/**
 * @brief     uri string handling implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/uri.h>
#include <string.h>

//****************************************************************************
// returns the index into the uri marking the beginning of the
// fragment substring. If no fragment exists, the result will be < 0.
static int32_t taa_uri_findfragmentoffset(
    const char* uri)
{
    const char* s = strchr(uri, '#');
    return (s != NULL) ? ((int32_t) (s - uri)) + 1 : -1;
}

//****************************************************************************
// returns the index into the uri marking the beginning of the host
// substring. If no host exists, the result will be < 0.
static int32_t taa_uri_findhostoffset(
    const char* uri)
{
    const char* s = strstr(uri, "://");
    return (s != NULL) ? ((int32_t) (s - uri)) + 3 : -1;
}

//****************************************************************************
// returns the index into the uri marking the beginning of the path
// substring. If no path exists, the result will be < 0.
static int32_t taa_uri_findpathoffset(
    const char* uri)
{
    int32_t p;
    const char* s;

    // get the location of the host in the uri
    p = taa_uri_findhostoffset(uri);
    if(p >= 0)
    {
        // If the host exists, find the next '/'
        s = strchr(uri + p, '/');
        if(s != NULL)
        {
            p = ((int32_t) (s - uri)) + 1;
        }
        else
        {
            p = -1;
        }
    }
    else if(uri[0] == '/')
    {
        // If no host exists, search for the separator '/' at the
        // beginning of the string to indicate the uri begins with a path
        p = 1;
    }
    return p;
}

//****************************************************************************
static void taa_uri_cleanpath(
    char* uri)
{
    int32_t p;
    char* path;
    char* ch;
    int32_t off;

    p = taa_uri_findpathoffset(uri);
    if(p >= 0)
    {
        path = uri + p;
        ch = path;
        while(*ch != '\0' && *ch != '#')
        {
            if(*ch == '.')
            {
                if(ch[1] == '.')
                {
                    // move up to the parent folder
                    if(ch == path)
                    {
                        // if the '..' sequence is at the beginning of
                        // the path, leave it in place.
                        ch += 2;
                        continue;
                    }
                    off = ((int32_t) (ch - path)) - 1;
                    if(off > 0)
                    {
                        --off;
                        if(off > 0 && path[off] == '/')
                        {
                            --off;
                        }
                        while(off > 0 && path[off] != '/')
                        {
                            --off;
                        }
                    }
                    if(off == 0)
                    {
                        ++ch;
                    }
                    strcpy(path + off, ch + 2);
                    ch = path + off;
                    continue;
                }
                else if(ch[1] == '/')
                {
                    // referencing the current folder
                    if(ch == path)
                    {
                        // if the './' sequence is at the beginning of
                        // the path, leave it in place.
                        ++ch;
                    }
                    else
                    {
                        // since a slash was moved into this slot,
                        // back up to make sure it's not redundant
                        --ch;
                    }
                    continue;
                }
            }
            else if(*ch == '/')
            {
                // remove redundant slashes
                if(ch[1] == '/' || ch[1] == '\\')
                {
                    strcpy(ch, ch + 1);
                    continue;
                }
            }
            else if(*ch == '\\')
            {
                // convert back slashes to forward slashes.
                *ch = '/';
                continue;
            }
            ++ch;
        }
        if(*path == '/')
        {
            // if the path begins with '/', it is redundant, get rid of it
            strcpy(path, path + 1);
        }
    }
}

//****************************************************************************
void taa_uri_appendpath(
    char* uri,
    uint32_t urisize,
    const char* rel_path)
{
    int32_t p;
    int32_t f;
    uint32_t len;
    char* path;
    char s[taaURI_SIZE];

    if(rel_path[0] != '\0')
    {
        // find the beginning of the fragment in the existing string
        // and make a back up copy
        f = taa_uri_findfragmentoffset(uri);
        strcpy(s, uri);

        // chop off the fragment from the string
        if(f > 0)
        {
            uri[f - 1] = '\0';
        }
        // find the beginning of the path in the existing string.
        // The path should not write over anything before this.
        p = taa_uri_findpathoffset(uri);
        path = uri;
        if(p < 0)
        {
            // If a path doesn't exist, create one.
            p = (int32_t) strlen(uri);
            p = (p + 1 < taaURI_SIZE) ? p : 0;
            uri[p] = '/';
            ++p;
            uri[p] = '\0';
        }
        // point32_t to the path.
        path += p;

        // append the path to the existing path
        len = (uint32_t) strlen(path);
        if(len != 0 && (p + len + 1) < urisize)
        {
            // if there was already an existing path, ensure
            // there is a separator between the old path and the new one.
            path[len] = '/';
            ++len;
            path[len] = '\0';
        }
        strncpy(path + len, rel_path, urisize - (p + len));
        uri[urisize - 1] = '\0';

        // put the fragment back on the end of the path
        if(f >= 0)
        {
            len = (uint32_t) strlen(uri);
            strncpy(uri + len, "#", urisize - len);
            strncpy(uri + len + 1, s + f, urisize - (len + 1));
        }

        taa_uri_cleanpath(uri);
    }
}

//****************************************************************************
void taa_uri_getextension(
    const char* uri,
    char* extout,
    uint32_t size)
{
    int32_t p;
    int32_t f;
    uint32_t extLen;
    const char* dot;

    p = taa_uri_findpathoffset(uri);
    if(p >= 0)
    {
        dot = strchr(uri + p, '.');
        if(dot != NULL)
        {
            p = ((int32_t) (dot - uri)) + 1;
            f = taa_uri_findfragmentoffset(uri);
            if(f > p)
            {
                extLen = f - p;
                size = (extLen < size) ? extLen : size;
            }
            strncpy(extout, uri + p, size);
        }
        else if(size > 0)
        {
            *extout = '\0';
        }
    }
    else if(size > 0)
    {
        *extout = '\0';
    }
    if(size > 0)
    {
        extout[size - 1] = '\0';
    }
}

//****************************************************************************
void taa_uri_getfilename(
    const char* uri,
    char* fileout,
    uint32_t size)
{
    int32_t p;
    int32_t f;
    uint32_t pathLen;
    const char* slash;

    p = taa_uri_findpathoffset(uri);
    if(p >= 0)
    {
        f = taa_uri_findfragmentoffset(uri);
        if(f > p)
        {
            slash = strchr(uri + p, '/');
            while(slash != NULL && slash < (uri + f))
            {
                p = ((int32_t) (slash - uri)) + 1;
                slash = strchr(uri + p, '/');
            }
            // subtract one for the '#' separator,
            // and add one for the null terminator
            pathLen = f - p;
            size = (pathLen < size) ? pathLen : size;
        }
        else
        {
            slash = strrchr(uri + p, '/');
            if(slash != NULL)
            {
                p = ((int32_t) (slash - uri)) + 1;
            }
        }
        strncpy(fileout, uri + p, size);
    }
    else if(size > 0)
    {
        *fileout = '\0';
    }
    if(size > 0)
    {
        fileout[size - 1] = '\0';
    }
}

//****************************************************************************
void taa_uri_getfragment(
    const char* uri,
    char* fragmentout,
    uint32_t size)
{
    int32_t f;

    f = taa_uri_findfragmentoffset(uri);
    if(f >= 0)
    {
        strncpy(fragmentout, uri + f, size);
    }
    else if(size > 0)
    {
        *fragmentout = '\0';
    }
    if(size > 0)
    {
        fragmentout[size - 1] = '\0';
    }
}

//****************************************************************************
void taa_uri_gethost(
    const char* uri,
    char* hostout,
    uint32_t size)
{
    int32_t h;
    int32_t p;
    uint32_t hostLen;

    h = taa_uri_findhostoffset(uri);
    if(h >= 0)
    {
        p = taa_uri_findpathoffset(uri);
        if(p < 0)
        {
            p = taa_uri_findfragmentoffset(uri);
        }
        if(p > h)
        {
            // subtract one for the separator,
            // and add one for the null terminator
            hostLen = p - h;
            size = (hostLen < size) ? hostLen : size;
            strncpy(hostout, uri + h, size);
        }
        else
        {
            strncpy(hostout, uri + h, size);
        }
    }
    else if(size > 0)
    {
        *hostout = '\0';
    }
    if(size > 0)
    {
        hostout[size - 1] = '\0';
    }
}

//****************************************************************************
void taa_uri_getpath(
    const char* uri,
    char* pathout,
    uint32_t size)
{
    int32_t p;
    int32_t f;
    uint32_t pathLen;

    p = taa_uri_findpathoffset(uri);
    if(p >= 0)
    {
        f = taa_uri_findfragmentoffset(uri);
        if(f > p)
        {
            // subtract one for the '#' separator,
            // and add one for the null terminator
            pathLen = f - p;
            size = (pathLen < size) ? pathLen : size;
        }
        strncpy(pathout, uri + p, size);
    }
    else if(size > 0)
    {
        *pathout = '\0';
    }
    if(size > 0)
    {
        pathout[size - 1] = '\0';
    }
}

//****************************************************************************
void taa_uri_getprotocol(
    const char* uri,
    char* protocolout,
    uint32_t size)
{
    int32_t h;
    uint32_t protocolLen;

    h = taa_uri_findhostoffset(uri);
    if(h >= 0)
    {
        // subtract three for the '://' separator,
        // and add one for the null terminator
        protocolLen = h - 3 + 1;
        size = (protocolLen < size) ? protocolLen : size;
        strncpy(protocolout, uri, size);
    }
    else if(size > 0)
    {
        *protocolout = '\0';
    }
    if(size > 0)
    {
        protocolout[size - 1] = '\0';
    }
}

//****************************************************************************
void taa_uri_set(
    const char* s,
    char* uriout,
    uint32_t urisize)
{
    if(s != NULL)
    {
        strncpy(uriout, s, urisize - 1);
        uriout[urisize - 1] = '\0';
    }
    else
    {
        uriout[0] = '\0';
    }
    taa_uri_cleanpath(uriout);
}

//****************************************************************************
void taa_uri_setfragment(
    char* uri,
    uint32_t urisize,
    const char* fragment)
{
    int32_t f;

    f = taa_uri_findfragmentoffset(uri);
    if(fragment[0] == '#')
    {
        // If the new fragment contains its own '#', skip past it
        ++fragment;
    }
    if(f < 0)
    {
        // If there was no previously set fragment in the uri,
        // add the '#' to the end of the path.
        f = (int32_t) strlen(uri);
        uri[f] = '#';
        ++f;
    }
    if(fragment[0] != '\0')
    {
        // If the new fragment is not empty, concatenate it to the
        // end of the uri.
        strncpy(uri + f, fragment, urisize - f);
    }
    else
    {
        // If the new fragment is empty, chop the '#' off end of the uri
        uri[f - 1] = '\0';
    }

    // force the uri to be null terminated
    uri[urisize - 1] = '\0';
}

//****************************************************************************
void taa_uri_sethost(
    char* uri,
    uint32_t urisize,
    const char* host)
{
    int32_t h;
    int32_t p;
    int32_t f;
    int32_t len;
    char s[taaURI_SIZE];

    // Get the beginning and ending of the host in the string and make
    // a back up copy
    h = taa_uri_findhostoffset(uri);
    p = taa_uri_findpathoffset(uri);
    f = taa_uri_findfragmentoffset(uri);
    strcpy(s, uri);

    len = (int32_t) strlen(host);
    if(h < 0)
    {
        // If no separator between the host and protocol exists,
        // the protocol has not been set yet either, so add the separator
        // to the beginning of the string.
        strncpy(uri, "://", urisize);
        h = 3;
    }
    // Copy the new host int32_to the uri at the appropriate position
    strncpy(uri + h, host, urisize - h);
    // Insert the separator for the path
    uri[h + len] = '/';
    ++len;
    if(p >= 0)
    {
        // If a path exists, copy it back in
        strncpy(uri + h + len, s + p, urisize - (h + len));
    }
    else if(f >= 0)
    {
        // If no path existed, but a fragment was there, insert
        // the fragment back in.
        uri[h + len] = '#';
        ++len;
        strncpy(uri + h + len, s + f, urisize - (h + len));
    }

    // force the uri to be null terminated
    uri[urisize - 1] = '\0';
}

//****************************************************************************
void taa_uri_setpath(
    char* uri,
    uint32_t urisize,
    const char* path)
{
    int32_t p;
    int32_t f;

    p = taa_uri_findpathoffset(uri);
    if(p >= 0)
    {
        // Chop off the old path
        f = taa_uri_findfragmentoffset(uri);
        if(f > p)
        {
            // If a fragment exists, move it over where the original
            // path was located.
            uri[p] = '#';
            strcpy(uri + p + 1, uri + f);
        }
        else
        {
            // If no fragment is specified, truncate the string
            uri[p] = '\0';
        }
    }

    // Insert the new path
    taa_uri_appendpath(uri, urisize, path);
}

//****************************************************************************
void taa_uri_setprotocol(
    char* uri,
    uint32_t urisize,
    const char* protocol)
{
    int32_t h;
    int32_t len;
    char s[taaURI_SIZE];

    // Get the beginning and ending of the host in the string and make
    // a back up copy
    h = taa_uri_findhostoffset(uri);
    strcpy(s, uri);

    // copy the new protocol int32_to the uri and insert the separator
    len = (int32_t) strlen(protocol);
    strncpy(uri, protocol, urisize);
    strncpy(uri + len, "://",  urisize - len);
    len += 3;

    // the two different paths here are necessary to prevent duplicating
    // the '://' separator if it previously existed in the string.
    if(h >= 0)
    {
        // if a host existed, insert it back in.
        strncpy(uri + len, s + h, urisize - len);
    }
    else
    {
        // otherwise, just copy the contents of the old uri back in
        strncpy(uri + len, s, urisize - len);
    }

    // force the uri to be null terminated
    uri[urisize - 1] = '\0';
}
