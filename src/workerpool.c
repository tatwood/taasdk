#include <taa/workerpool.h>
#include <taa/semaphore.h>
#include <taa/thread.h>
#include <stdlib.h>

typedef struct taa_workerpool_threaddata_s taa_workerpool_threaddata;

struct taa_workerpool_threaddata_s
{
    int32_t index;
    taa_thread thread;
    taa_semaphore sem;
    taa_workerpool* workerpool;
};

struct taa_workerpool_s
{
    taa_semaphore sem;
    taa_workqueue* workqueue;
    taa_workerpool_threaddata* threads;
    uint32_t numthreads;
    int32_t quit;
    taa_workerpool_startfunc startfunc;
    taa_workerpool_stopfunc stopfunc;
    void* startdata;
    void* stopdata;
};

//****************************************************************************
static taa_thread_result taa_THREAD_CALLCONV taa_workerpool_thread(
    void* args)
{
    taa_workerpool_threaddata* td = (taa_workerpool_threaddata*) args;
    taa_workerpool* wp = td->workerpool;
    taa_workqueue* wq = wp->workqueue;
    // wait for first post before proceeding into job loop
    taa_semaphore_wait(&td->sem);
    // if an initialization function was provided, execute it
    if(wp->startfunc != NULL)
    {
        wp->startfunc(td->index, wp->startdata);
    }
    // tell the main thread that initialization is complete
    taa_semaphore_post(&wp->sem);
    // loop until the quit signal is sent
    while(!wp->quit)
    {
        taa_workqueue_func jobfunc;
        void* userdata;
        if(taa_workqueue_pop(wq, 1, &jobfunc, &userdata))
        {
            jobfunc(userdata);
        }
    }
    // if a shutdown function was provided, execute it
    if(wp->stopfunc != NULL)
    {
        wp->stopfunc(td->index, wp->stopdata);
    }
    return 0;
}

//****************************************************************************
void taa_workerpool_create(
    uint32_t numthreads,
    taa_workqueue* wq,
    taa_workerpool** wp_out)
{
    uintptr_t offset = 0;
    taa_workerpool* wp;
    taa_workerpool_threaddata* td;
    taa_workerpool_threaddata* tdend;
    int32_t i;
    // determine buffer size and pointer offsets
    wp = (taa_workerpool*) offset;
    offset = (uintptr_t) (wp + 1);
    td = (taa_workerpool_threaddata*) taa_ALIGN_PTR(offset, 8);
    offset = (uintptr_t) (td + numthreads);
    // allocate the buffer and adjust pointers
    offset = (uintptr_t) calloc(1, offset);
    wp = (taa_workerpool*) (((uintptr_t) wp) + offset);
    td = (taa_workerpool_threaddata*) (((uintptr_t) td) + offset);
    tdend = td + numthreads;
    // initialize workqueue struct
    taa_semaphore_create(&wp->sem);
    wp->workqueue = wq;
    wp->threads = td;
    wp->numthreads = numthreads;
    // initialize threads
    i = 0;
    while(td != tdend)
    {
        td->index = i++;
        td->workerpool = wp;
        taa_semaphore_create(&td->sem);
        // thread must be started last, after everything else is ready
        taa_thread_create(taa_workerpool_thread, td, &td->thread);
        ++td;
    }
    // set out parameter
    *wp_out = wp;
}

//****************************************************************************
void taa_workerpool_destroy(
    taa_workerpool* wp)
{
    taa_workerpool_threaddata* td;
    taa_workerpool_threaddata* tdend;
    // make sure threads are shutdown
    if(!wp->quit)
    {
        taa_workerpool_stop(wp, NULL, NULL);
    }
    // clean up data for each thread
    td = wp->threads;
    tdend = td + wp->numthreads;
    while(td != tdend)
    {
        taa_semaphore_destroy(&td->sem);
        ++td;
    }
    taa_semaphore_destroy(&wp->sem);
    // free buffer
    free(wp);
}

//****************************************************************************
void taa_workerpool_start(
    taa_workerpool* wp,
    taa_workerpool_startfunc startfunc,
    void* userdata)
{
    taa_workerpool_threaddata* td = wp->threads;
    taa_workerpool_threaddata* tdend = td + wp->numthreads;
    // save the init function and userdata pointers
    wp->startfunc = startfunc;
    wp->startdata = userdata;
    // notify all the threads
    while(td != tdend)
    {
        taa_semaphore_post(&td->sem);
        ++td;
    }
    // wait for all the threads to signal that they are ready
    td = wp->threads;
    while(td != tdend)
    {
        taa_semaphore_wait(&wp->sem);
        ++td;
    }
}

//****************************************************************************
void taa_workerpool_stop(
    taa_workerpool* wp,
    taa_workerpool_stopfunc stopfunc,
    void* userdata)
{
    taa_workerpool_threaddata* td = wp->threads;
    taa_workerpool_threaddata* tdend = td + wp->numthreads;
    // save the shutdown function and userdata pointers
    wp->stopfunc = stopfunc;
    wp->stopdata = userdata;
    // instruct the threads to exit
    wp->quit = 1;
    // stop threads from waiting for jobs
    taa_workqueue_abort(wp->workqueue);
    // wait for all the threads to exit
    td = wp->threads;
    while(td != tdend)
    {
        taa_thread_join(td->thread);
        ++td;
    }
}
