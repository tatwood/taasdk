/**
 * @brief     coroutine implementation for platforms without fibers
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by coroutine.c
#ifdef taa_COROUTINE_C_

// this file provides a coroutine implementation using setjmp/longjmp
// and stack pointer manipulation. this solution may cause issues with c++
// features such as exception unwinding and should only be used in the absence
// of a native solution for the target platform.
#include <taa/coroutine.h>
#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>

//****************************************************************************

// override longjmp stack protection on gcc. this could be done by redefining
// __USE_FORTIFY_LEVEL to 0, but that may not work or play well with other
// source files if they are included together in the same compilation unit.
// this method, while relying on compiler internals, keeps changes local.
#if defined(__GNUC__) && __USE_FORTIFY_LEVEL > 0
#pragma push_macro("longjmp")
#pragma push_macro("setjmp")
#undef longjmp
#undef setjmp
#define longjmp taa_coroutine_longjmp
#define setjmp _setjmp
// assembly redirection may have been used to point _longjmp at the checked
// implementation; create a new redirection that points to the real _longjmp	    
extern void taa_coroutine_longjmp(
    void* env,
    int val) __asm__("_longjmp") __attribute__ ((__noreturn__));			        
#endif

#if defined(__GNUC__) && defined(__i386__) // GCC, x86

// replace stack register and call function
#define taa_COROUTINE_LAUNCH(_func, _stack) \
    __asm__ __volatile__ ( \
    "movl %0, %%edx\n" \
    "movl %1, %%esp\n" \
    "call *%%edx" \
    : \
    : "r"(_func), "r"(_stack) \
    : "%esp", "%edx");
// x86 stack grows downward
#define taa_COROUTINE_STACKDIR 1

#elif defined(__GNUC__) && defined(__x86_64__) // GCC, x64

// replace stack register and call function
#define taa_COROUTINE_LAUNCH(_func, _stack) \
    __asm__ __volatile__ ( \
    "movq %0, %%rdx\n" \
    "movq %1, %%rsp\n" \
    "call *%%rdx" \
    : \
    : "r"(_func), "r"(_stack) \
    : "%rsp", "%rdx");
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

typedef struct taa_coroutine_impl_s taa_coroutine_impl;
typedef struct taa_coroutine_status_s taa_coroutine_status;

struct taa_coroutine_impl_s
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
    taa_coroutine_impl* active;
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
int taa_coroutine_create(
    size_t stacksize,
    taa_coroutine_func func,
    void* args,
    taa_coroutine* co_out)
{
    int err = -1;
    taa_coroutine_impl* coimpl;
    uint8_t* buf;
    uint8_t* stack;
    // alloc a buffer big enough for the stack and data
    buf = (uint8_t*) malloc(sizeof(*coimpl) + stacksize);
    if(buf != NULL)
    {
        coimpl = (taa_coroutine_impl*) buf;
        buf = (uint8_t*) (coimpl + 1);
        // put stack at beginning or end of buffer depending grow direction
        stack = buf + stacksize * taa_COROUTINE_STACKDIR;
        coimpl->func = func;
        coimpl->args = args;
        coimpl->stack = stack;
        coimpl->started = 0; //false
        *co_out = (taa_coroutine) coimpl;
        err = 0;
    }
    return err;
};

//****************************************************************************
int taa_coroutine_destroy(
    taa_coroutine co)
{
    free(co);
    return 0;
}

//****************************************************************************
int taa_coroutine_execute(
    taa_coroutine co)
{
    volatile taa_coroutine_status* tls;
    // initialize the base context
    tls = &taa_tls_coroutine_status;
    tls->active = (taa_coroutine_impl*) co;
    setjmp(((taa_coroutine_status*) tls)->basejmp);
    // all coroutines jump here when switched or done
    tls = &taa_tls_coroutine_status;
    if(tls->active != NULL)
    {
        if(!tls->active->started)
        {
            // jump hasn't been created for the coroutine yet, so launch it
            void* stack = tls->active->stack;
            taa_COROUTINE_LAUNCH(taa_coroutine_wrapper, stack)
            // never reaches here; jumps back to base context
        }
        // jump into a coroutine that has already been launched
        longjmp(tls->active->jmpbuf, 1);
        // never reaches here; jumps back to base context
    }
    return 0;
}

//****************************************************************************
void taa_coroutine_switch(
    taa_coroutine co)
{
    taa_coroutine_status* tls = &taa_tls_coroutine_status;
    // save the active coroutine
    assert(tls->active != NULL); // only can be called from within a coroutine
    if(!setjmp(tls->active->jmpbuf))
    {
        // set the new coroutine
        tls->active = (taa_coroutine_impl*) co;
        // jump back to the base context
        longjmp(tls->basejmp, 1);
    }
}

#undef taa_COROUTINE_LAUNCH
#undef taa_COROUTINE_STACKDIR

// restore gcc stack protection
#if defined(__GNUC__) && __USE_FORTIFY_LEVEL > 0
#pragma pop_macro("longjmp")
#pragma pop_macro("setjmp")
#endif

#endif // taa_COROUTINE_C_

