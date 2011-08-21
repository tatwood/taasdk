/**
 * @brief     target agnostic wrapper for C99 stdint header typedefs
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_STDINT_H_
#define TAA_STDINT_H_

#ifdef _MSC_FULL_VER

// MSVC does not provide stdint.h
typedef __int8 int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;

typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

#else

#include <stdint.h>

#endif

#endif // TAA_STDINT_H_
