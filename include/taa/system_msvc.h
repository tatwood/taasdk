/**
 * @brief     miscellaneous system function header for msvc
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_SYSTEM_MSVC_H_
#define TAA_SYSTEM_MSVC_H_

#define taa_ATOMIC_CMPXCHG32_TARGET(pval, oldval, newval) \
    InterlockedCompareExchange((LONG*) (pval), newval, oldval)

#define taa_ATOMIC_CMPXCHGPTR_TARGET(pptr, oldptr, newptr) \
    InterlockedCompareExchangePointer (pptr, newptr, oldptr)

#define taa_ATOMIC_DEC32_TARGET(pval) \
    InterlockedDecrement((LONG*) (pval))

#define taa_ATOMIC_INC32_TARGET(pval) \
    InterlockedIncrement((LONG*) (pval))

#define taa_ATOMIC_XCHG32_TARGET(pval, newval) \
    InterlockedExchange((LONG*) (pval), newval)

#define taa_ATOMIC_XCHGPTR_TARGET(pptr, newptr) \
    InterlockedExchangePointer(pptr, newptr)

#define taa_BFS32_TARGET(pindex_out, mask) \
    (_BitScanForward(reinterpret_cast<unsigned long*>(pindex_out), mask))

// MSVC does not support C99 inline keyword
#define taa_INLINE_TARGET __inline

#if 0
// disabled until a suitable gcc implementation is found
#define taaBTR_32_TARGET(pbits, index) \
    (_bittestandreset(reinterpret_cast<long*>(pbits), index))

#define taaBTS_32_TARGET(pbits, index) \
    (_bittestandset(reinterpret_cast<long*>(pbits), index))
#endif

#define taa_THREADLOCAL_TARGET __declspec(thread)
#define taa_THREADLOCAL_EXTERN_TARGET __declspec(thread) extern
#define taa_THREADLOCAL_STATIC_TARGET __declspec(thread) static

#endif // TAA_SYSTEM_MSVC_H_
