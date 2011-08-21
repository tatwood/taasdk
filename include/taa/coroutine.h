/**
 * @brief     target agnostic coroutine management header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_COROUTINE_H_
#define TAA_COROUTINE_H_

#include "system.h"

typedef void (*taa_coroutine_func)(void* args);

typedef struct taa_coroutine_s taa_coroutine;

taa_EXTERN_C void taa_coroutine_create(
    uint32_t stacksize,
    taa_coroutine_func func,
    void* args,
    taa_coroutine* cout);

taa_EXTERN_C void taa_coroutine_destroy(
    taa_coroutine* c);

taa_EXTERN_C void taa_coroutine_execute(
    taa_coroutine* c);

taa_EXTERN_C void taa_coroutine_switch(
    taa_coroutine* c);

#ifdef WIN32
#include "coroutine_win32.h"
#else
#include "coroutine_other.h"
#endif

#endif // TAA_COROUTINE_H_
