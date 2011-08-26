/**
 * @brief     lightweight splinlock header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_SPINLOCK_H_
#define TAA_SPINLOCK_H_

#include "thread.h"

typedef struct taa_spinlock_s taa_spinlock;

struct taa_spinlock_s
{
    volatile int32_t lock;
    taa_thread_id threadid;
    uint32_t refcount;
    uint32_t padding;
};

//****************************************************************************

taa_EXTERN_C void taa_spinlock_create(
    taa_spinlock* lockout);

taa_EXTERN_C void taa_spinlock_destroy(
    taa_spinlock* lock);

taa_EXTERN_C void taa_spinlock_lock(
    taa_spinlock* lock);

taa_EXTERN_C void taa_spinlock_unlock(
    taa_spinlock* lock);

#endif // TAA_SPINLOCK_H_
