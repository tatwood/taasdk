/**
 * @brief     target agnostic header for miscellaneous system functions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SYSTEM_H_
#define taa_SYSTEM_H_

#include <stdint.h>
#include <stddef.h>

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

//****************************************************************************
// macros

#define taa_ATTRIB_ALIGN(align_) \
    taa_ATTRIB_ALIGN_TARGET(align_)

#define taa_DECLSPEC_ALIGN(align_) \
    taa_DECLSPEC_ALIGN_TARGET(align_)

#define taa_ATTRIB_MAY_ALIAS \
    taa_ATTRIB_MAY_ALIAS_TARGET

#define taa_ALIGN_PTR(ptr_, align_) \
    ((void*) ((((uintptr_t) (ptr_)) + ((align_)-1)) & ~((align_)-1)))

#define taa_BSF32(pindex_out, mask_) \
    taa_BFS32_TARGET(pindex_out, mask_)

#define taa_PAUSE() \
    taa_PAUSE_TARGET()

#define taa_INLINE taa_INLINE_TARGET

#define taa_THREADLOCAL taa_THREADLOCAL_TARGET
#define taa_THREADLOCAL_EXTERN taa_THREADLOCAL_EXTERN_TARGET
#define taa_THREADLOCAL_STATIC taa_THREADLOCAL_STATIC_TARGET

#ifndef taa_SDK_LINKAGE
#define taa_SDK_LINKAGE
#endif

//****************************************************************************
// enums

enum taa_statmode_e
{
    taa_S_IFREG = taa_S_IFREG_TARGET,
    taa_S_IFDIR = taa_S_IFDIR_TARGET
};

//****************************************************************************
// typedefs

typedef enum taa_statmode_e taa_statmode;

typedef struct taa_dir_s* taa_dir;

//****************************************************************************
// structs

struct taa_stat
{
    taa_statmode st_mode;
    size_t st_size;
};

//****************************************************************************
// functions

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_chdir(
    const char* path);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_closedir(
    taa_dir dir);

/**
 * @return path_out on success, NULL on error
 */
taa_SDK_LINKAGE char* taa_getcwd(
    char* path_out,
    uint32_t pathsize);

taa_SDK_LINKAGE void* taa_memalign(
    size_t align,
    size_t size);

taa_SDK_LINKAGE void taa_memalign_free(
    void* p);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_opendir(
    const char* path,
    taa_dir* dir_out);

taa_SDK_LINKAGE const char* taa_readdir(
    taa_dir dir);

taa_SDK_LINKAGE void taa_sleep(
    uint32_t ms);

taa_SDK_LINKAGE void taa_sched_yield();

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_stat(
    const char* path,
    struct taa_stat* st_out);

#endif // taa_SYSTEM_H_
