/**
 * @brief     an asychronous work scheduler implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/workqueue.h>
#include <taa/semaphore.h>
#include <taa/thread.h>
#include <stdlib.h>

typedef struct taa_workqueue_node_s taa_workqueue_node;

struct taa_workqueue_node_s
{
    taa_workqueue_func workfunc;
    taa_workqueue_callback callback;
    void* userdata;
    int32_t result;
    taa_workqueue_node* next;
};

struct taa_workqueue_s
{
    taa_workqueue_node* worklist;
    taa_workqueue_node* callbacklist;
    taa_workqueue_node* pool;
    volatile int32_t quit;
    taa_window_display windisp;
    taa_rendercontext rc;
    taa_semaphore worksem;
    taa_semaphore mainsem;
    taa_thread thread;
};

//****************************************************************************
static taa_workqueue_node* taa_workqueue_popnodes(
    taa_workqueue_node** list)
{
    taa_workqueue_node* node = *list;
    taa_workqueue_node* prev;
    do
    {
        prev = node;
        node = taa_ATOMIC_CMPXCHGPTR(list, node, NULL);
    }
    while(node != prev);
    return node;
}

//****************************************************************************
static void taa_workqueue_pushnode(
    taa_workqueue_node** list,
    taa_workqueue_node* node)
{
    taa_workqueue_node* next;
    node->next = *list;
    do
    {
        next = node->next;
        node->next = taa_ATOMIC_CMPXCHGPTR(list, node->next, node);
    }
    while(node->next != next);
}


//****************************************************************************
static int taa_workqueue_thread(
    void* args)
{
    taa_workqueue* wq = (taa_workqueue*) args;
    taa_workqueue_node* node = NULL;
    taa_rendercontext_makecurrent(&wq->windisp, &wq->rc);
    taa_semaphore_post(&wq->mainsem);
    while(!wq->quit)
    {
        if(node == NULL)
        { 
            node = taa_workqueue_popnodes(&wq->worklist);
        }
        if(node != NULL)
        {
            taa_workqueue_node* next = node->next;
            node->result = node->workfunc(node->userdata);
            taa_workqueue_pushnode(&wq->callbacklist, node);
            node = next;
        }
        else
        {
            // if there was nothing to process, wait for a post
            taa_semaphore_wait(&wq->worksem);
        }
    }
    //make sure all aborted nodes are put into callback list
    do
    {
        while(node != NULL)
        {
            taa_workqueue_node* next = node->next;
            taa_workqueue_pushnode(&wq->callbacklist, node);
            node = next;
        }
        if(node == NULL)
        { 
            node = taa_workqueue_popnodes(&wq->worklist);
        }
    }
    while(node != NULL);
    taa_rendercontext_makecurrent(&wq->windisp, NULL);
    return 0;
}

//****************************************************************************
void taa_workqueue_create(
    taa_window_display* windisp,
    taa_rendercontext* rc,
    uint32_t capacity,
    taa_workqueue** wqout)
{
    taa_workqueue* wq;
    taa_workqueue_node* node;
    taa_workqueue_node* nodeend;
    uint32_t size = sizeof(*wq) + sizeof(*node)*capacity;
    void* buf = malloc(size);
    wq = (taa_workqueue*) buf;
    buf = wq + 1;

    wq->pool = (taa_workqueue_node*) buf;
    node = wq->pool;
    nodeend = node + capacity - 1;
    while(node != nodeend)
    {
        node->next = node + 1;
        ++node;
    }
    node->next = NULL;

    wq->windisp = *windisp;
    taa_rendercontext_createshared(rc, &wq->rc);
    taa_semaphore_create(&wq->worksem);
    taa_semaphore_create(&wq->mainsem);
    wq->worklist = NULL;
    wq->callbacklist = NULL;
    wq->quit = 0;
    taa_thread_create(taa_workqueue_thread, wq, &wq->thread);
    taa_semaphore_wait(&wq->mainsem);
    *wqout = wq;
}

//****************************************************************************
void taa_workqueue_destroy(
    taa_workqueue* wq)
{
    wq->quit = 1;
    taa_semaphore_post(&wq->worksem);
    taa_thread_join(&wq->thread);
    taa_semaphore_destroy(&wq->mainsem);
    taa_semaphore_destroy(&wq->worksem);
    taa_rendercontext_destroy(&wq->rc);
    free(wq);
}

//****************************************************************************
void taa_workqueue_push(
    taa_workqueue* wq,
    taa_workqueue_func workfunc,
    taa_workqueue_callback callback,
    void* userdata)
{
    // acquire a request node
    taa_workqueue_node* node = wq->pool;
    taa_workqueue_node* prev;
    do
    {
        while(node == NULL)
        {
            taa_thread_yield();
            node = wq->pool;
        }
        prev = node;
        node = taa_ATOMIC_CMPXCHGPTR(&wq->pool, node, node->next);
    }
    while(prev != node);
    // set its members
    node->workfunc = workfunc;
    node->callback = callback;
    node->userdata = userdata;
    node->result = -1;
    // push it to the load list
    taa_workqueue_pushnode(&wq->worklist, node);
    // post a signal to the worker thread
    taa_semaphore_post(&wq->worksem);
}

//****************************************************************************
void taa_workqueue_update(
    taa_workqueue* wq)
{
    taa_workqueue_node* node = taa_workqueue_popnodes(&wq->callbacklist);
    while(node != NULL)
    {
        taa_workqueue_node* next = node->next;
        // perform callback
        if(node->callback != NULL)
        {
            node->callback(node->result, node->userdata);
        }
        // put request back in pool
        taa_workqueue_pushnode(&wq->pool, node);
        node = next;
    }
}
