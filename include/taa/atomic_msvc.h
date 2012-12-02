/**
 * @brief     msvc header for atomic operation macros
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_ATOMIC_MSVC_H_
#define taa_ATOMIC_MSVC_H_

#define taa_ATOMIC_AND_32_TARGET(pval, mask) \
    _InterlockedAnd(pval, mask)

#define taa_ATOMIC_CMPXCHG_32_TARGET(pval, oldval, newval) \
    _InterlockedCompareExchange((LONG*) (pval), newval, oldval)

#define taa_ATOMIC_CMPXCHG_PTR_TARGET(pptr, oldptr, newptr) \
    _InterlockedCompareExchangePointer (pptr, newptr, oldptr)

#define taa_ATOMIC_DEC_32_TARGET(pval) \
    _InterlockedDecrement((LONG*) (pval))

#define taa_ATOMIC_INC_32_TARGET(pval) \
    _InterlockedIncrement((LONG*) (pval))

#define taa_ATOMIC_XCHG_32_TARGET(pval, newval) \
    _InterlockedExchange((LONG*) (pval), newval)

#define taa_ATOMIC_XCHG_PTR_TARGET(pptr, newptr) \
    _InterlockedExchangePointer(pptr, newptr)

#endif // taa_ATOMIC_MSVC_H_
