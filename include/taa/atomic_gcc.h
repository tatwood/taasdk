/**
 * @brief     gcc header for atomic operation macros
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_ATOMIC_GCC_H_
#define taa_ATOMIC_GCC_H_

#define taa_ATOMIC_AND_32_TARGET(pval, mask) \
	__sync_and_and_fetch(pval, mask)

#define taa_ATOMIC_CMPXCHG_32_TARGET(pval, oldval, newval) \
    __sync_val_compare_and_swap(pval, oldval, newval)

#define taa_ATOMIC_CMPXCHG_PTR_TARGET(pptr, oldptr, newptr) \
    __sync_val_compare_and_swap(pptr, oldptr, newptr)

#define taa_ATOMIC_DEC_32_TARGET(pval) \
    __sync_sub_and_fetch(pval, 1)

#define taa_ATOMIC_INC_32_TARGET(pval) \
    __sync_add_and_fetch(pval, 1)

#define taa_ATOMIC_XCHG_32_TARGET(pval, newval) \
    __sync_lock_test_and_set(pval, newval)

#define taa_ATOMIC_XCHG_PTR_TARGET(pptr, newptr) \
    __sync_lock_test_and_set(pptr, newptr)

#endif // taa_ATOMIC_GCC_H_
