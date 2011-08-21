/**
 * @brief     thread management implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by thread.c
#ifdef TAA_THREAD_C_

#include <process.h>
#include <stdlib.h>

typedef struct taa_thread_args_s taa_thread_args;

struct taa_thread_args_s
{
    taa_thread_func func;
    void* args;
};

//****************************************************************************
static uint32_t __stdcall taa_thread_wrapper(
    void* args)
{
    taa_thread_args targs = *((taa_thread_args*) args);
    free(args);
    return targs.func(targs.args);
}

//****************************************************************************
void taa_thread_create(
    taa_thread_func func,
    void* args,
    taa_thread* tout)
{
    taa_thread_args* targs = (taa_thread_args*) malloc(sizeof(*targs));
    uintptr_t h;

    targs->func = func;
    targs->args = args;

    h = _beginthreadex(NULL, 0,taa_thread_wrapper,targs,0,&tout->win32.id);
    tout->win32.h = (HANDLE) h;
}

//****************************************************************************
taa_thread_id taa_thread_currentid()
{
    return (taa_thread_id) GetCurrentThreadId();
}

//****************************************************************************
int32_t taa_thread_equal(
    taa_thread_id a,
    taa_thread_id b)
{
    return a == b;
}

//****************************************************************************
taa_thread_id taa_thread_getid(
    taa_thread* t)
{
    return (taa_thread_id) t->win32.id;
}

//****************************************************************************
int taa_thread_join(
    taa_thread* t)
{
    DWORD ret;
    WaitForSingleObject(t->win32.h, INFINITE);
    GetExitCodeThread(t->win32.h, &ret);
    CloseHandle(t->win32.h);
    return (int) ret;
}

//****************************************************************************
void taa_thread_sleep(
    uint32_t ms)
{
    Sleep(ms);
}

//****************************************************************************
void taa_thread_yield()
{
    SwitchToThread();
}

#endif // TAA_THREAD_C_

