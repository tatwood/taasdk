/**
 * @brief     futex implementation for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by futex.c
#ifdef taa_FUTEX_C_
#include <taa/futex.h>

int taa_futex_create(
    taa_futex* ftx_out)
{
    int err = 0;
    pthread_mutexattr_t attr;
    err = pthread_mutexattr_init(&attr);
    if(err == 0)
    {
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        err = pthread_mutex_init(ftx_out, &attr);
        pthread_mutexattr_destroy(&attr);
    }
    return err;
}

int taa_futex_destroy(
    taa_futex* ftx)
{
    return pthread_mutex_destroy(ftx);
}

int taa_futex_lock(
    taa_futex* ftx)
{
    return pthread_mutex_lock(ftx);
}

int taa_futex_unlock(
    taa_futex* ftx)
{
    return pthread_mutex_unlock(ftx);
}

#endif // taa_FUTEX_C_
