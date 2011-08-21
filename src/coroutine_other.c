/**
 * @brief     coroutine implementation for platforms without fibers
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by coroutine.c
#ifdef TAA_COROUTINE_C_

// This file provides a custom coroutine implementation using setjmp/longjmp
// and stack pointer manipulation. This solution may cause issues with C++
// features such as exception unwinding and should only be used is the absence
// of a native solution for the target platform.
#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>

//****************************************************************************

#if defined(__GNUC__) && defined(__i386__) // GCC, x86

// replace stack register and call function
#define taa_COROUTINE_LAUNCH(_func, _stack) \
    asm volatile ("movl %0, %%edx\n" \
                  "movl %1, %%esp\n" \
                  "call *%%edx" \
                  : \
                  : "r"(_func), "r"(_stack) \
                  : "%esp", "%edx");
// x86 stack grows downward
#define taa_COROUTINE_STACKDIR 1

#elif defined(_MSC_FULL_VER) && defined(_M_IX86) // MSVC, x86

// replace stack register and call function
#define taa_COROUTINE_LAUNCH(_func, _stack) \
    _asm \
    { \
        _asm mov  edx, dword ptr[_func] \
        _asm mov  esp, dword ptr[_stack] \
        _asm call edx \
    }
// x86 stack grows downward
#define taa_COROUTINE_STACKDIR 1

#else
#error coroutines not implemented for this platform
#endif

// ***************************************************************************

typedef struct taa_coroutine_other_s taa_coroutine_other;
typedef struct taa_coroutine_status_s taa_coroutine_status;

struct taa_coroutine_other_s
{
    jmp_buf jmpbuf;
    taa_coroutine_func func;
    void* args;
    void* stack;
    int started;
};

struct taa_coroutine_status_s
{
    jmp_buf basejmp;
    taa_coroutine_other* active;
};

taa_THREADLOCAL_STATIC taa_coroutine_status taa_tls_coroutine_status;

//****************************************************************************
static void taa_coroutine_wrapper()
{
    // initialize the coroutine
    volatile taa_coroutine_status* tls = &taa_tls_coroutine_status;
    tls->active->started = 1; // true
    while(1)
    {
        // execute the coroutine
        tls->active->func(tls->active->args);
        // finished coroutine function, reset the jump to return here
        tls = &taa_tls_coroutine_status;
        if(!setjmp(tls->active->jmpbuf))
        {
            // clear the active coroutine and jump back to the base context
            tls->active = NULL;
            longjmp(((taa_coroutine_status*) tls)->basejmp, 1);
        }
        tls = &taa_tls_coroutine_status;
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
    taa_coroutine_other* other;
    uint8_t* buf;
    uint8_t* stack;
    buf = (uint8_t*) malloc(sizeof(*other) + stacksize);

    other = (taa_coroutine_other*) buf;
    buf = (uint8_t*) (other + 1);
    // put stack at beginning or end of buffer depending on direction it grows
    stack = buf + stacksize * taa_COROUTINE_STACKDIR;

    other->func = func;
    other->args = args;
    other->stack = stack;
    other->started = 0; //false
    cout->other = other;
};

//****************************************************************************
void taa_coroutine_destroy(
    taa_coroutine* c)
{
    free(c->other);
}

//****************************************************************************
void taa_coroutine_execute(
    taa_coroutine* c)
{
    volatile taa_coroutine_status* tls;

    // initialize the base context
    tls = &taa_tls_coroutine_status;
    tls->active = (taa_coroutine_other*) c->other;
    setjmp(((taa_coroutine_status*) tls)->basejmp);
    // all coroutines jump here when switched or done

    tls = &taa_tls_coroutine_status;
    if(tls->active != NULL)
    {
        if(!tls->active->started)
        {
            // jump hasn't been created for the corotouine yet, so launch it
            void* stack = tls->active->stack;
            taa_COROUTINE_LAUNCH(taa_coroutine_wrapper, stack)
            // never reaches here; jumps back to base context
        }
        // jump into a coroutine that has already been launched
        longjmp(tls->active->jmpbuf, 1);
        // never reaches here; jumps back to base context
    }
}

//****************************************************************************
void taa_coroutine_switch(
    taa_coroutine* c)
{
    taa_coroutine_status* tls = &taa_tls_coroutine_status;

    // save the active coroutine
    assert(tls->active != NULL); // only can be called from within a coroutine
    if(!setjmp(tls->active->jmpbuf))
    {
        // set the new coroutine
        tls->active = (taa_coroutine_other*) c->other;
        // jump back to the base context
        longjmp(tls->basejmp, 1);
    }
}

#undef taa_COROUTINE_LAUNCH
#undef taa_COROUTINE_STACKDIR

#endif // TAA_COROUTINE_C_
