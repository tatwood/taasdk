/**
 * @brief     miscellaneous system function header for gcc
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SYSTEM_GCC_H_
#define taa_SYSTEM_GCC_H_

#define taa_ATTRIB_ALIGN_TARGET(align_) __attribute__ ((aligned (align_)))

#define taa_DECLSPEC_ALIGN_TARGET(align_)

#define taa_ATTRIB_MAY_ALIAS_TARGET __attribute__ ((__may_alias__))

#define taa_BSF32_TARGET(pindex_out, mask) \
    (*(pindex_out) = __builtin_ctz(mask))

#if defined(__i386__) || defined(__x86_64__)    
#define taa_PAUSE_TARGET() __asm__ __volatile__ ("pause"::);
#endif

#define taa_INLINE_TARGET inline

#define taa_THREADLOCAL_TARGET __thread
#define taa_THREADLOCAL_EXTERN_TARGET extern __thread
#define taa_THREADLOCAL_STATIC_TARGET static __thread

#endif // taa_SYSTEM_GCC_H_
