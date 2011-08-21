/**
 * @brief     uri string handling header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_URI_H_
#define TAA_URI_H_

#include "system.h"

enum
{
    taaURI_SIZE = 256
};

void taa_uri_appendpath(
    char* uri,
    uint32_t urisize,
    const char* rel_path);

void taa_uri_getextension(
    const char* uri,
    char* extout,
    uint32_t size);

void taa_uri_getfilename(
    const char* uri,
    char* fileout,
    uint32_t size);

void taa_uri_getfragment(
    const char* uri,
    char* fragmentout,
    uint32_t size);

void taa_uri_gethost(
    const char* uri,
    char* hostout,
    uint32_t size);

void taa_uri_getpath(
    const char* uri,
    char* pathout,
    uint32_t size);

void taa_uri_getprotocol(
    const char* uri,
    char* protocolout,
    uint32_t size);

void taa_uri_set(
    const char* s,
    char* uriout,
    uint32_t urisize);

void taa_uri_setfragment(
    char* uri,
    uint32_t urisize,
    const char* fragment);

void taa_uri_sethost(
    char* uri,
    uint32_t urisize,
    const char* host);

void taa_uri_setpath(
    char* uri,
    uint32_t urisize,
    const char* path);

void taa_uri_setprotocol(
    char* uri,
    uint32_t urisize,
    const char* protocol);

#endif // TAA_URI_H_
