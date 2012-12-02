/**
 * @brief     miscellaneous system function header for msvc
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SYSTEM_MSVC_H_
#define taa_SYSTEM_MSVC_H_

#include <xmmintrin.h>

#define taa_ATTRIB_ALIGN_TARGET(align_)

#define taa_DECLSPEC_ALIGN_TARGET(align_) __declspec(align(align_))

#define taa_ATTRIB_MAY_ALIAS_TARGET

#define taa_BSF32_TARGET(pindex_out, mask) \
    (_BitScanForward(reinterpret_cast<unsigned long*>(pindex_out), mask))

#define taa_PAUSE_TARGET() _mm_pause()

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

#endif // taa_SYSTEM_MSVC_H_
