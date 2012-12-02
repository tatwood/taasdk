/**
 * @brief     Macros for primitive non-reentrant spin lock
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SPINLOCK_H_
#define taa_SPINLOCK_H_

#include "atomic.h"
#include "system.h"

/**
 * @brief lock
 * @details Spins in a loop until it is able to change the lock value from 0
 * to 1. This macro will always busy wait and may cause poor performance if
 * used incorrectly. This lock is non-reentrant; if a thread attempts to
 * recursively enter the lock while it already owns it, it will deadlock.
 * @param lock_ an integer variable representing the lock. The lock should be
 * initialized to 0 before use.
 */
#define taa_SPINLOCK_LOCK(plock_) \
    do{ \
        unsigned i_ = 0; \
        while(taa_ATOMIC_CMPXCHG_32(plock_, 0, 1) != 0) \
        { \
            taa_PAUSE(); \
            if((i_ & 64) == 63) \
            { \
                taa_sched_yield(); \
            } \
            ++i_; \
        } \
    }while(0)

/**
 * @brief unlock
 */
#define taa_SPINLOCK_UNLOCK(plock_) \
    do{ *(plock_) = 0; }while(0)

#endif // taa_SPINLOCK_H_
