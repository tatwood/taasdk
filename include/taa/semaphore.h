/**
 * @brief     target agnostic semaphore management header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_SEMAPHORE_H_
#define TAA_SEMAPHORE_H_

#include "system.h"

typedef struct taa_semaphore_s taa_semaphore;

taa_EXTERN_C void taa_semaphore_create(
    taa_semaphore* sem);

taa_EXTERN_C void taa_semaphore_destroy(
    taa_semaphore* sem);

/// increment count
taa_EXTERN_C void taa_semaphore_post(
    taa_semaphore* sem);

/// decrement count and wait until count > 0
taa_EXTERN_C void taa_semaphore_wait(
    taa_semaphore* sem);

#ifdef WIN32
#include "semaphore_win32.h"
#else
#include "semaphore_posix.h"
#endif

#endif // TAA_SEMAPHORE_H_
