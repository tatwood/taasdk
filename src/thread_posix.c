/**
 * @brief     thread management implementation for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by thread.c
#ifdef TAA_THREAD_C_

#include <poll.h>
#include <sched.h>
#include <stdlib.h>

typedef struct taa_thread_args_s taa_thread_args;

struct taa_thread_args_s
{
    taa_thread_func func;
    void* args;
};

//****************************************************************************
static void* taa_thread_wrapper(
    void* args)
{
    taa_thread_args targs = *((taa_thread_args*) args);
    free(args);
    return (void*) targs.func(targs.args);
}

//****************************************************************************
void taa_thread_create(
    taa_thread_func func,
    void* args,
    taa_thread* tout)
{
    taa_thread_args* targs = (taa_thread_args*) malloc(sizeof(*targs));
    pthread_attr_t attr;

    targs->func = func;
    targs->args = args;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&tout->posix, &attr, taa_thread_wrapper, targs);
    pthread_attr_destroy(&attr);
}

//****************************************************************************
taa_thread_id taa_thread_currentid()
{
    return (taa_thread_id) pthread_self();
}

//****************************************************************************
int32_t taa_thread_equal(
    taa_thread_id a,
    taa_thread_id b)
{
    return pthread_equal((pthread_t) a, (pthread_t) b);
}

//****************************************************************************
taa_thread_id taa_thread_getid(
    taa_thread* t)
{
    return (taa_thread_id) t->posix;
}

//****************************************************************************
int32_t taa_thread_join(
    taa_thread* t)
{
    void* ret;
    pthread_join(t->posix, &ret);
    return (int32_t) ret;
}

//****************************************************************************
void taa_thread_sleep(
    uint32_t ms)
{
    poll(NULL, 0, ms);
}

//****************************************************************************
void taa_thread_yield()
{
    sched_yield();
}

#endif // TAA_THREAD_C_
