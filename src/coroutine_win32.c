/**
 * @brief     coroutine implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by coroutine.c
#ifdef TAA_COROUTINE_C_

#include <stdlib.h>

typedef struct taa_coroutine_win32_s taa_coroutine_win32;

struct taa_coroutine_win32_s
{
    LPVOID fiber;
    taa_coroutine_func func;
    void* args;
};

taa_THREADLOCAL_STATIC LPVOID taa_tls_coroutine_status;

//****************************************************************************
static void __stdcall taa_coroutine_wrapper(void* args)
{
    while(1)
    {
        taa_coroutine_win32* win32 = (taa_coroutine_win32*) args;
        // execute the function
        win32->func(win32->args);
        // instead of returning and killing the thread, switch back to the
        // primary fiber for this thread, which will then convert the fiber
        // back into a normal thread.
        SwitchToFiber(taa_tls_coroutine_status);
    }
    // never reaches here
}

//****************************************************************************
void taa_coroutine_create(
    uint32_t stacksize,
    taa_coroutine_func func,
    void* args,
    taa_coroutine* cout)
{
    // alloc a buffer big enough for the stack and data
    taa_coroutine_win32* win32 = (taa_coroutine_win32*)malloc(sizeof(*win32));
    win32->fiber = CreateFiber(stacksize, taa_coroutine_wrapper, win32);
    win32->func = func;
    win32->args = args;
    cout->win32 = win32;
};

//****************************************************************************
void taa_coroutine_destroy(
    taa_coroutine* c)
{
    taa_coroutine_win32* win32 = (taa_coroutine_win32*) c->win32;
    DeleteFiber(win32->fiber);
    free(win32);
}

//****************************************************************************
void taa_coroutine_execute(
    taa_coroutine* c)
{
    taa_coroutine_win32* win32 = (taa_coroutine_win32*) c->win32;
    taa_tls_coroutine_status = ConvertThreadToFiber(NULL);
    SwitchToFiber(win32->fiber);
    ConvertFiberToThread();
}

//****************************************************************************
void taa_coroutine_switch(
    taa_coroutine* c)
{
    taa_coroutine_win32* win32 = (taa_coroutine_win32*) c->win32;
    SwitchToFiber(win32->fiber);
}

#endif // TAA_COROUTINE_C_
