/**
 * @brief     target agnostic header for miscellaneous system functions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_SYSTEM_H_
#define TAA_SYSTEM_H_

#include "stdint.h"

//****************************************************************************
// macros

#define taa_ALIGN8(ptr_) ((void*) ((((uintptr_t) (ptr_))+7) & ~7))

#define taa_ALIGN16(ptr_) ((void*) ((((uintptr_t) (ptr_))+15) & ~15))

#define taa_ATOMIC_CMPXCHG32(pval_, oldval_, newval_) \
    taa_ATOMIC_CMPXCHG32_TARGET(pval_, oldval_, newval_)

#define taa_ATOMIC_CMPXCHGPTR(pptr_, oldptr_, newptr_) \
    taa_ATOMIC_CMPXCHGPTR_TARGET(pptr_, oldptr_, newptr_)

#define taa_ATOMIC_DEC32(pval_) \
    taa_ATOMIC_DEC32_TARGET(pval_)

#define taa_ATOMIC_INC32(pval_) \
    taa_ATOMIC_INC32_TARGET(pval_)

#define taa_ATOMIC_XCHG32(pval_, newval_) \
    taa_ATOMIC_XCHG32_TARGET(pval_, newval_)

#define taa_ATOMIC_XCHGPTR(pptr_, newptr_) \
    taa_ATOMIC_XCHGPTR_TARGET(pptr_, newptr_)

#define taa_BFS32(pindex_out, mask_) \
    taa_BFS32_TARGET(pindex_out, mask_)

#define taa_INLINE taa_INLINE_TARGET

#define taa_THREADLOCAL taa_THREADLOCAL_TARGET
#define taa_THREADLOCAL_EXTERN taa_THREADLOCAL_EXTERN_TARGET
#define taa_THREADLOCAL_STATIC taa_THREADLOCAL_STATIC_TARGET

#ifdef __cplusplus
#define taa_EXTERN_C extern "C"
#else
#define taa_EXTERN_C extern
#endif

//****************************************************************************
// typedefs

typedef enum taa_filemode_e taa_filemode;
typedef struct taa_dir_s taa_dir;
typedef struct taa_filestat_s taa_filestat;

//****************************************************************************
// enums

enum taa_filemode_e
{
    taa_FILE_IFDIR,
    taa_FILE_IFREG
};

//****************************************************************************
// structs

struct taa_filestat_s
{
    taa_filemode mode;
    uint32_t size;
};

//****************************************************************************
// functions

/**
 * @return 0 on success, -1 on error
 */
taa_EXTERN_C int taa_chdir(
    const char* path);

taa_EXTERN_C void taa_closedir(
    taa_dir* dir);

/**
 * @return pathout on success, NULL on error
 */
taa_EXTERN_C char* taa_getcwd(
    char* pathout,
    uint32_t pathsize);

/**
 * @return 0 on success, -1 on error
 */
taa_EXTERN_C int taa_getfilestat(
    const char* path,
    taa_filestat* out);

/**
 * in nanoseconds
 */
taa_EXTERN_C void taa_getsystemtime(uint64_t* nsout);

/**
 * @return 0 on success, -1 on error
 */
taa_EXTERN_C int taa_opendir(
    const char* path,
    taa_dir* dirout);

taa_EXTERN_C const char* taa_readdir(
    taa_dir* dir);

#ifdef __GNUC__
#include "system_gcc.h"
#endif

#ifdef _MSC_FULL_VER
#include "system_msvc.h"
#endif

#ifdef WIN32
#include "system_win32.h"
#else
#include "system_posix.h"
#endif

#endif // TAA_SYSTEM_H_
