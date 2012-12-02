/**
 * @brief     path string handling header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_PATH_H_
#define taa_PATH_H_

#include <taa/system.h>

#ifdef WIN32
enum
{
    taa_PATH_SLASH_TARGET = '\\',
    taa_PATH_SIZE_TARGET = 256 // actual windows limit is 260
};
#else
enum
{
    taa_PATH_SLASH_TARGET = '/',
    taa_PATH_SIZE_TARGET = 256 // this is an arbitrary number
};
#endif

enum
{
    taa_PATH_SLASH = taa_PATH_SLASH_TARGET,
    taa_PATH_SIZE = taa_PATH_SIZE_TARGET
};

//****************************************************************************

taa_SDK_LINKAGE void taa_path_append(
    char* path,
    uint32_t pathsize,
    const char* relpath);

/***
 * @brief retrieves the base file name, excluding extension.
 */
taa_SDK_LINKAGE void taa_path_get_base(
    const char* path,
    char* base_out,
    uint32_t sz);

taa_SDK_LINKAGE void taa_path_get_dir(
    const char* path,
    char* dir_out,
    uint32_t sz);

taa_SDK_LINKAGE void taa_path_get_ext(
    const char* path,
    char* ext_out,
    uint32_t sz);

/***
 * @brief retrieves the file name, including extension.
 */
taa_SDK_LINKAGE void taa_path_get_file(
    const char* path,
    char* file_out,
    uint32_t sz);

taa_SDK_LINKAGE int taa_path_is_absolute(
    const char* path);

taa_SDK_LINKAGE void taa_path_set(
    char* path,
    uint32_t pathsize,
    const char* src);

taa_SDK_LINKAGE void taa_path_set_ext(
    char* path,
    uint32_t pathsize,
    const char* ext);

#endif // taa_PATH_H_
