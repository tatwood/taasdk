/**
 * @brief     target agnostic semaphore header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SEMAPHORE_H_
#define taa_SEMAPHORE_H_

#include "system.h"

#ifdef WIN32
#include "semaphore_win32.h"
#else
#include "semaphore_posix.h"
#endif

/**
 * @details On posix systems, this is a (sem_t), and on win32, it is a
 * semaphore (HANDLE).
 */
typedef taa_semaphore_target taa_semaphore;

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_semaphore_create(
    taa_semaphore* sem_out);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_semaphore_destroy(
    taa_semaphore* sem);

/**
 * @brief increment count
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_semaphore_post(
    taa_semaphore* sem);

/**
 * @brief decrement count and wait until count > 0
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_semaphore_wait(
    taa_semaphore* sem);

#endif // taa_SEMAPHORE_H_
