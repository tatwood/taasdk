/**
 * @brief     thread management implementation for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by thread.c
#ifdef taa_THREAD_C_
#include <taa/thread.h>
#include <sched.h>
#include <unistd.h>

//****************************************************************************
int taa_thread_create(
    taa_thread_func func,
    void* args,
    taa_thread* t_out)
{
    int32_t err = 0;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    err = pthread_create(
        (pthread_t*) t_out,
        &attr,
        (void *(*)(void*)) func,
        args);
    pthread_attr_destroy(&attr);
    return err;
}

//****************************************************************************
int taa_thread_equal(
    taa_thread_id a,
    taa_thread_id b)
{
    return pthread_equal((pthread_t) a, (pthread_t) b);
}

//****************************************************************************
#if 0
// no windows equivalent exists pre-vista
taa_thread_id taa_thread_getid(
    taa_thread t)
{
    return (taa_thread_id) t;
}
#endif

//****************************************************************************
taa_thread_result taa_thread_join(
    taa_thread t)
{
    void* ret;
    pthread_join((pthread_t) t, &ret);
    return (taa_thread_result) ret;
}

//****************************************************************************
taa_thread_id taa_thread_self()
{
    return (taa_thread_id) pthread_self();
}

#endif // taa_THREAD_C_

