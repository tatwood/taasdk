/**
 * @brief     custom reentrant user space lock
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef CFUTEX_H_
#define CFUTEX_H_

#include <taa/atomic.h>
#include <taa/semaphore.h>
#include <taa/thread.h>
#include <assert.h>
#include <string.h>

enum
{
    CFUTEX_LOOPS = 64
};

typedef struct cfutex_s cfutex;

struct cfutex_s
{
    taa_semaphore sem;
    taa_thread_id threadid;
    uint32_t lock;
    uint32_t owners;
    uint32_t waiters;
};

//****************************************************************************
int cfutex_create(
    cfutex* ftx_out)
{
    memset(ftx_out, 0, sizeof(*ftx_out));
    return taa_semaphore_create(&ftx_out->sem);
}

//****************************************************************************
void cfutex_destroy(
    cfutex* ftx)
{
    taa_semaphore_destroy(&ftx->sem);
}

//****************************************************************************
void cfutex_lock(
    cfutex* ftx)
{
    taa_thread_id curthread = taa_thread_self();
    if(ftx->owners != 0 && taa_thread_equal(curthread, ftx->threadid))
    {
        // this thread already owns the lock; just increment it
        ++ftx->owners;
    }
    else
    {
        int iswaiter = 0;
        int i = 0;
        while(1)
        {
            int trylock = (ftx->owners == 0);
            // if maximum busy wait attempts have been made, then idle wait.
            // also, if any thread decides to idle wait, in the interest of
            // fairness, all the threads should do the same.
            if((i >= CFUTEX_LOOPS) || (ftx->waiters > 0))
            {
                if(iswaiter || (taa_ATOMIC_INC_32(&ftx->waiters) > 1))
                {
                    // can only wait if the count was already positive.
                    // if the count was zero, the lock owner may have
                    // released the lock before realizing a post was needed.
                    taa_semaphore_wait(&ftx->sem);
                }
                iswaiter = 1;                
                // since this thread was either the first to change the waiter
                // count from 0 to 1, or was awakened by semaphore, it gets
                // first attempt at ownership.
                trylock = 1;
                // reset busy loop counter after each wait
                i = 0;
            }
            if(trylock)
            {
                while(taa_ATOMIC_CMPXCHG_32(&ftx->lock, 0, 1) != 0)
                {
                    taa_PAUSE();
                }
                if(ftx->owners == 0)
                {
                    // successfully gained ownership
                    if(iswaiter)
                    {
                        taa_ATOMIC_DEC_32(&ftx->waiters);
                    }
                    ftx->threadid = curthread;
                    assert(ftx->owners == 0);
                    ftx->owners = 1;
                    ftx->lock = 0;
                    break;
                }
                ftx->lock = 0;
            }
            taa_sched_yield();
            ++i;
        }
    }
}

//****************************************************************************
void cfutex_unlock(
    cfutex* ftx)
{
    assert(taa_thread_equal(taa_thread_self(), ftx->threadid));
    if(ftx->owners == 1)
    {
        // ownership is about to be released, need to be careful to prevent
        // posts from being missed.
        while(taa_ATOMIC_CMPXCHG_32(&ftx->lock, 0, 1) != 0)
        {
            taa_PAUSE();
        }
        if(ftx->waiters > 0)
        {
            taa_semaphore_post(&ftx->sem);
        }
        ftx->owners = 0;
        ftx->lock = 0;
    }
    else
    {
        --ftx->owners;
    }
}

#endif // CFUTEX_H_
