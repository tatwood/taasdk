/**
 * @brief     path string handling header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_PATH_H_
#define TAA_PATH_H_

#include <taa/system.h>

#ifdef WIN32
enum
{
    taa_PATH_SLASH_PLATFORM = '\\',
    taa_PATH_SIZE_PLATFORM = 256 // actual windows limit is 260
};
#else
enum
{
    taa_PATH_SLASH_PLATFORM = '/',
    taa_PATH_SIZE_PLATFORM = 256 // this is an arbitrary number
};
#endif

enum
{
    taa_PATH_SLASH = taa_PATH_SLASH_PLATFORM,
    taa_PATH_SIZE = taa_PATH_SIZE_PLATFORM
};

//****************************************************************************

taa_EXTERN_C void taa_path_append(
    char* path,
    uint32_t pathsize,
    const char* relpath);

taa_EXTERN_C int taa_path_isabsolute(
    const char* path);

taa_EXTERN_C void taa_path_getbase(
    const char* path,
    char* baseout,
    uint32_t sz);

taa_EXTERN_C void taa_path_getdir(
    const char* path,
    char* dirout,
    uint32_t sz);

taa_EXTERN_C void taa_path_getext(
    const char* path,
    char* extout,
    uint32_t sz);

taa_EXTERN_C void taa_path_getfile(
    const char* path,
    char* fileout,
    uint32_t sz);

taa_EXTERN_C void taa_path_set(
    char* pathout,
    uint32_t pathsize,
    const char* src);

taa_EXTERN_C void taa_path_setext(
    char* path,
    uint32_t pathsize,
    const char* ext);

#endif // TAA_PATH_H_
