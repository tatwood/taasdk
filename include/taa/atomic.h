/**
 * @brief     target agnostic header for atomic operation macros
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_ATOMIC_H_
#define taa_ATOMIC_H_

#ifdef __GNUC__
#include "atomic_gcc.h"
#endif

#ifdef _MSC_FULL_VER
#include "atomic_msvc.h"
#endif

/**
 * @return resulting value of the and operation
 */
#define taa_ATOMIC_AND_32(pval_, mask_) \
    taa_ATOMIC_AND_32_TARGET(pval_, mask_)

#define taa_ATOMIC_CMPXCHG_32(pval_, oldval_, newval_) \
    taa_ATOMIC_CMPXCHG_32_TARGET(pval_, oldval_, newval_)

#define taa_ATOMIC_CMPXCHG_PTR(pptr_, oldptr_, newptr_) \
    taa_ATOMIC_CMPXCHG_PTR_TARGET(pptr_, oldptr_, newptr_)

/**
 * @return resulting decremented value
 */
#define taa_ATOMIC_DEC_32(pval_) \
    taa_ATOMIC_DEC_32_TARGET(pval_)

/**
 * @return resulting incremented value
 */
#define taa_ATOMIC_INC_32(pval_) \
    taa_ATOMIC_INC_32_TARGET(pval_)

#define taa_ATOMIC_XCHG_32(pval_, newval_) \
    taa_ATOMIC_XCHG_32_TARGET(pval_, newval_)

#define taa_ATOMIC_XCHG_PTR(pptr_, newptr_) \
    taa_ATOMIC_XCHG_PTR_TARGET(pptr_, newptr_)

#endif // taa_ATOMIC_H_
