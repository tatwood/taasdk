/**
 * @brief     coroutine implementation for win32 target
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by coroutine.c
#ifdef taa_COROUTINE_C_
#include <taa/coroutine.h>
#include <stdlib.h>

typedef struct taa_coroutine_win32_s taa_coroutine_args;

struct taa_coroutine_win32_s
{
    taa_coroutine_func func;
    void* userdata;
};

taa_THREADLOCAL_STATIC LPVOID taa_tls_coroutine_status;

//****************************************************************************
static void __stdcall taa_coroutine_wrapper(void* args)
{
    taa_coroutine_args* coargs = (taa_coroutine_args*) args;
    taa_coroutine_func func = coargs->func;
    void* userdata = coargs->userdata;
    free(args);
    while(1)
    {
        // execute the function
        func(userdata);
        // instead of returning and killing the thread, switch back to the
        // primary fiber for this thread, which will then convert the fiber
        // back into a normal thread.
        SwitchToFiber(taa_tls_coroutine_status);
    }
    // never reaches here
}

//****************************************************************************
int taa_coroutine_create(
    size_t stacksize,
    taa_coroutine_func func,
    void* userdata,
    taa_coroutine* co_out)
{
    // alloc a buffer big enough for the stack and data
    taa_coroutine_args* arg = (taa_coroutine_args*)malloc(sizeof(*arg));
    HANDLE h;
    arg->func = func;
    arg->userdata = userdata;
    h = CreateFiber(stacksize,taa_coroutine_wrapper,arg);
    *co_out = h;
    return (h != NULL) ? 0 : -1;
};

//****************************************************************************
int taa_coroutine_destroy(
    taa_coroutine co)
{
    DeleteFiber((LPVOID) co);
    return 0;
}

//****************************************************************************
int taa_coroutine_execute(
    taa_coroutine co)
{
    int err = -1;
    taa_tls_coroutine_status = ConvertThreadToFiber(NULL);
    if(taa_tls_coroutine_status != NULL)
    {
        SwitchToFiber((LPVOID) co);
        err = ConvertFiberToThread() ? 0 : -1;
    }
    return err;
}

//****************************************************************************
void taa_coroutine_switch(
    taa_coroutine co)
{
    SwitchToFiber((LPVOID) co);
}

#endif // taa_COROUTINE_C_
