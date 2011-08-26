/**
 * @brief     lightweight splinlock implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/spinlock.h>
#include <assert.h>
#include <string.h>

//****************************************************************************
void taa_spinlock_create(
    taa_spinlock* lockout)
{
    memset(lockout, 0, sizeof(*lockout));
}

//****************************************************************************
void taa_spinlock_destroy(
    taa_spinlock* lock)
{
    // nothing to do
}

//****************************************************************************
void taa_spinlock_lock(
    taa_spinlock* lock)
{
    taa_thread_id curthread = taa_thread_currentid();
    do
    {
        while(taa_ATOMIC_CMPXCHG32(&lock->lock, 0, 1) == 1)
        {
            taa_thread_yield();
        }
        if(lock->refcount == 0 || taa_thread_equal(lock->threadid,curthread))
        {
            break;            
        }
        taa_thread_yield();
    }
    while(1);
    lock->threadid = curthread;
    ++lock->refcount;
    lock->lock = 0;
}

//****************************************************************************
void taa_spinlock_unlock(
    taa_spinlock* lock)
{
    while(taa_ATOMIC_CMPXCHG32(&lock->lock, 0, 1) == 1)
    {
       taa_thread_yield();
    }
    --lock->refcount;
    lock->lock = 0;
}

