/**
 * @brief     mutex implementation for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by mutex.c
#ifdef taa_MUTEX_C_
#include <taa/mutex.h>

int taa_mutex_create(
    taa_mutex* mtx_out)
{
    int err = 0;
    pthread_mutexattr_t attr;
    err = pthread_mutexattr_init(&attr);
    if(err == 0)
    {
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        err = pthread_mutex_init(mtx_out, &attr);
        pthread_mutexattr_destroy(&attr);
    }
    return err; 
}

int taa_mutex_destroy(
    taa_mutex* mtx)
{
    return pthread_mutex_destroy(mtx);
}

int taa_mutex_lock(
    taa_mutex* mtx)
{
    return pthread_mutex_lock(mtx);
}

int taa_mutex_unlock(
    taa_mutex* mtx)
{
    return pthread_mutex_unlock(mtx);
}

#endif // taa_MUTEX_C_

