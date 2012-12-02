/**
 * @brief     reentrant user space lock header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_FUTEX_H_
#define taa_FUTEX_H_

#include "system.h"

#ifdef WIN32
#include "futex_win32.h"
#else
#include "futex_posix.h"
#endif

/**
 * @details On posix systems, this is a pthread_mutex_t set to 
 * PTHREAD_MUTEX_RECURSIVE. On win32, it is a CRITICAL_SECTION. The
 * pthread_mutex_t implementation on linux is much faster than the heavyweight
 * win32 mutex, eliminating the need for a separate futex type on that
 * platform.
 */
typedef taa_futex_target taa_futex;

//****************************************************************************

taa_SDK_LINKAGE int taa_futex_create(
    taa_futex* ftx_out);

taa_SDK_LINKAGE int taa_futex_destroy(
    taa_futex* ftx);

taa_SDK_LINKAGE int taa_futex_lock(
    taa_futex* ftx);

taa_SDK_LINKAGE int taa_futex_unlock(
    taa_futex* ftx);

#endif // taa_FUTEX_H_
