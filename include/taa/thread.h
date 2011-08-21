/**
 * @brief     target agnostic thread management header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_THREAD_H_
#define TAA_THREAD_H_

#include "system.h"

//****************************************************************************
// typedefs

typedef int (*taa_thread_func)(void* args);

typedef uintptr_t taa_thread_id;
typedef struct taa_thread_s taa_thread;

//****************************************************************************
// extern functions

taa_EXTERN_C void taa_thread_create(
    taa_thread_func func,
    void* args,
    taa_thread* tout);

taa_EXTERN_C taa_thread_id taa_thread_currentid();

taa_EXTERN_C int32_t taa_thread_equal(
    taa_thread_id a,
    taa_thread_id b);

taa_EXTERN_C taa_thread_id taa_thread_getid(
    taa_thread* t);

taa_EXTERN_C int32_t taa_thread_join(
    taa_thread* t);

taa_EXTERN_C void taa_thread_sleep(
    uint32_t ms);

taa_EXTERN_C void taa_thread_yield();

//****************************************************************************
// platform includes

#ifdef WIN32
#include "thread_win32.h"
#else
#include "thread_posix.h"
#endif

#endif // TAA_THREAD_H_
