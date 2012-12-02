/**
 * @brief     target agnostic mutex header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_MUTEX_H_
#define taa_MUTEX_H_

#include "system.h"

#ifdef WIN32
#include "mutex_win32.h"
#else
#include "mutex_posix.h"
#endif

/**
 * @details On posix systems, this is a pthread_mutex_t set to
 * PTHREAD_MUTEX_RECURSIVE. ; On win32, it is a mutex HANDLE.
 */
typedef taa_mutex_target taa_mutex;

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_mutex_create(
    taa_mutex* mtx_out);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_mutex_destroy(
    taa_mutex* mtx);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_mutex_lock(
    taa_mutex* mtx);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_mutex_unlock(
    taa_mutex* mtx);

#endif // taa_MUTEX_H_
