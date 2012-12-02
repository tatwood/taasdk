/**
 * @brief     an asychronous work scheduler implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/workqueue.h>
#include <taa/conditionvar.h>
#include <taa/mutex.h>
#include <stdlib.h>

typedef struct taa_workqueue_job_s taa_workqueue_job;
typedef struct taa_workqueue_list_s taa_workqueue_list;

struct taa_workqueue_job_s
{
    taa_workqueue_func  func;
    void* userdata;
    int32_t result;
    taa_workqueue_job* next;
};

struct taa_workqueue_list_s
{
    volatile uint32_t lock;
    taa_workqueue_job* head;
    taa_workqueue_job* tail;
};


struct taa_workqueue_s
{
    taa_mutex lock;
    taa_conditionvar condvar;
    taa_workqueue_list queue;
    taa_workqueue_list pool;
    int32_t abort;
    void* end;
};

//****************************************************************************
static taa_workqueue_job* taa_workqueue_list_pop(
    taa_workqueue_list* queue)
{
    taa_workqueue_job* job;
    // pop the job
    job = queue->head;
    if(job != NULL)
    {
        taa_workqueue_job* next = job->next;
        queue->head = next;
        if(next == NULL)
        {
            queue->tail = NULL;
        }
    }
    return job;
}

//****************************************************************************
static void taa_workqueue_list_push(
    taa_workqueue_list* queue,
    taa_workqueue_job* job)
{
    taa_workqueue_job* tail;
    // push the job
    tail = queue->tail;
    queue->tail = job;
    if(tail != NULL)
    {
        tail->next = job;
    }
    else
    {
        queue->head = job;
    }
    job->next = NULL;
}

//****************************************************************************
void taa_workqueue_abort(
    taa_workqueue* wq)
{
    taa_mutex_lock(&wq->lock);
    wq->abort = 1;
    taa_conditionvar_signal(&wq->condvar);
    taa_mutex_unlock(&wq->lock);
}

//****************************************************************************
void taa_workqueue_create(
    uint32_t capacity,
    taa_workqueue** wq_out)
{
    uintptr_t offset = 0;
    taa_workqueue* wq;
    taa_workqueue_job* j;
    taa_workqueue_job* jend;
    // determine buffer size and pointer offsets
    wq = (taa_workqueue*) offset;
    offset = (uintptr_t) (wq + 1);
    j = (taa_workqueue_job*) taa_ALIGN_PTR(offset, 8);
    offset = (uintptr_t) (j + capacity);
    // allocate the buffer and adjust pointers
    offset = (uintptr_t) calloc(1, offset);
    wq = (taa_workqueue*) (((uintptr_t) wq) + offset);
    j = (taa_workqueue_job*) (((uintptr_t) j) + offset);
    jend = j + capacity;
    // initialize workqueue struct
    taa_conditionvar_create(&wq->condvar);
    taa_mutex_create(&wq->lock);
    wq->pool.head = j;
    wq->pool.tail = jend - 1;
    wq->end = jend;
    // initialize job pool
    while(j != jend-1)
    {
        j->next = j + 1;
        ++j;
    }
    // set out parameter
    *wq_out = wq;
}

//****************************************************************************
void taa_workqueue_destroy(
    taa_workqueue* wq)
{
    taa_workqueue_job* job;
    taa_conditionvar_destroy(&wq->condvar);
    taa_mutex_destroy(&wq->lock);
    // make sure any overflow allocations are freed
    job = wq->queue.head;
    while(job != NULL)
    {
        taa_workqueue_job* next = job->next;
        if((((void*)job) < ((void*)wq)) || (((void*)job) > wq->end))
        {
            free(job); // free overflow
        }
        job = next;
    }
    // free buffer
    free(wq);
}

//****************************************************************************
int32_t taa_workqueue_pop(
    taa_workqueue* wq,
    int32_t block,
    taa_workqueue_func* func_out,
    void** data_out)
{
    int32_t retval = 0;
    if(wq->queue.head != NULL || block)
    {
        taa_mutex_lock(&wq->lock);
        if(!wq->abort)
        {
            while(1)
            {
                taa_workqueue_job* job;
                job = taa_workqueue_list_pop(&wq->queue);
                if(job != NULL)
                {
                    *func_out = job->func;
                    *data_out = job->userdata;
                    retval = 1;
                    if(((void*)job) >= ((void*)wq) && ((void*)job) < wq->end)
                    {
                        // put the job node back in the pool
                        taa_workqueue_list_push(&wq->pool, job);
                    }
                    else
                    {
                        // free overflow pointer
                        free(job);
                    }
                    break;
                }
                // no job found
                if(block)
                {
                    // wait for signal
                    taa_conditionvar_wait(&wq->condvar, &wq->lock);
                    if(wq->abort != 0)
                    {
                        // if woken up from an abort signal, repost it 
                        // so that other threads get woken up as well.
                        taa_conditionvar_signal(&wq->condvar);
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        taa_mutex_unlock(&wq->lock);
    }
    return retval;
}

//****************************************************************************
void taa_workqueue_push(
    taa_workqueue* wq,
    taa_workqueue_func func,
    void* userdata)
{
    taa_mutex_lock(&wq->lock);
    if(!wq->abort)
    {
        // attempt to get a job node from the pool
        taa_workqueue_job* job = taa_workqueue_list_pop(&wq->pool);
        if(job == NULL)
        {
            // if that didn't work, allocate an overflow node
            job = (taa_workqueue_job*) malloc(sizeof(*job));
            // TODO: log overflow warning
        }
        job->func = func;
        job->userdata = userdata;
        taa_workqueue_list_push(&wq->queue, job);
        taa_conditionvar_signal(&wq->condvar);
    }
    taa_mutex_unlock(&wq->lock);
}
