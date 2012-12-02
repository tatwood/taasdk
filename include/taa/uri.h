/**
 * @brief     uri string handling header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_URI_H_
#define taa_URI_H_

#include "system.h"

// TODO: this code has an obvious big gaping hole in that it doesn't provide
// escaping and unescaping.

enum
{
    taa_URI_SIZE = 256
};

taa_SDK_LINKAGE void taa_uri_append_path(
    char* uri,
    uint32_t urisize,
    const char* rel_path);

taa_SDK_LINKAGE void taa_uri_get_extension(
    const char* uri,
    char* ext_out,
    uint32_t size);

taa_SDK_LINKAGE void taa_uri_get_filename(
    const char* uri,
    char* file_out,
    uint32_t size);

taa_SDK_LINKAGE void taa_uri_get_fragment(
    const char* uri,
    char* fragment_out,
    uint32_t size);

taa_SDK_LINKAGE void taa_uri_get_host(
    const char* uri,
    char* host_out,
    uint32_t size);

taa_SDK_LINKAGE void taa_uri_get_path(
    const char* uri,
    char* path_out,
    uint32_t size);

taa_SDK_LINKAGE void taa_uri_get_scheme(
    const char* uri,
    char* scheme_out,
    uint32_t size);

taa_SDK_LINKAGE void taa_uri_set(
    char* uri,
    uint32_t urisize,
    const char* src);

taa_SDK_LINKAGE void taa_uri_set_fragment(
    char* uri,
    uint32_t urisize,
    const char* fragment);

taa_SDK_LINKAGE void taa_uri_set_host(
    char* uri,
    uint32_t urisize,
    const char* host);

taa_SDK_LINKAGE void taa_uri_set_path(
    char* uri,
    uint32_t urisize,
    const char* path);

taa_SDK_LINKAGE void taa_uri_set_scheme(
    char* uri,
    uint32_t urisize,
    const char* scheme);

#endif // taa_URI_H_
