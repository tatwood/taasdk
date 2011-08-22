/**
 * @brief     miscellaneous system function header for gcc
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_SYSTEM_GCC_H_
#define TAA_SYSTEM_GCC_H_

#define taa_ATOMIC_CMPXCHG32_TARGET(pval, oldval, newval) \
    __sync_val_compare_and_swap(pval, oldval, newval)

#define taa_ATOMIC_CMPXCHGPTR_TARGET(pptr, oldptr, newptr) \
    __sync_val_compare_and_swap(pptr, oldptr, newptr)

#define taa_ATOMIC_DEC32_TARGET(pval) \
    __sync_sub_and_fetch(pval, 1)

#define taa_ATOMIC_INC32_TARGET(pval) \
    __sync_add_and_fetch(pval, 1)

#define taa_ATOMIC_XCHG32_TARGET(pval, newval) \
    __sync_lock_test_and_set(pval, newval)

#define taa_ATOMIC_XCHGPTR_TARGET(pptr, newptr) \
    __sync_lock_test_and_set(pptr, newptr)

#define taa_BFS32_TARGET(pindex_out, mask) \
    (*(pindex_out) = __builtin_ctz(mask))

#define taa_INLINE_TARGET inline static

#define taa_THREADLOCAL_TARGET __thread
#define taa_THREADLOCAL_EXTERN_TARGET extern __thread
#define taa_THREADLOCAL_STATIC_TARGET static __thread

#endif // TAA_SYSTEM_GCC_H_
