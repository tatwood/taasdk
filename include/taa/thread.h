/**
 * @brief     target agnostic thread management header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_THREAD_H_
#define taa_THREAD_H_

#include "system.h"

#ifdef WIN32
#include "thread_win32.h"
#else
#include "thread_posix.h"
#endif

//****************************************************************************
// macros

/**
 * @brief The calling convention of native thread functions
 */
#define taa_THREAD_CALLCONV taa_THREAD_CALLCONV_TARGET

//****************************************************************************
// typedefs

/**
 * @brief An integer type for thread function return values
 */
typedef taa_thread_result_target taa_thread_result;

/**
 * @brief native thread function type
 */
typedef taa_thread_result (taa_THREAD_CALLCONV *taa_thread_func)(void* args);

typedef uintptr_t taa_thread_id;

/**
 * @details On posix systems, this is a pthread_t. On win32, it is a thread
 * HANDLE.
 */
typedef taa_thread_target taa_thread;

//****************************************************************************
// functions

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int32_t taa_thread_create(
    taa_thread_func func,
    void* args,
    taa_thread* t_out);

/**
 * @brief Comparison of thread ids should always be performed by this function
 */
taa_SDK_LINKAGE int taa_thread_equal(
    taa_thread_id a,
    taa_thread_id b);

taa_SDK_LINKAGE taa_thread_result taa_thread_join(
    taa_thread t);

/**
 * @brief returns the id of the currently executing thread
 */
taa_SDK_LINKAGE taa_thread_id taa_thread_self();

#endif // taa_THREAD_H_
