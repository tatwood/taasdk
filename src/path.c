/**
 * @brief     path string handling implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/path.h>
#include <string.h>

//****************************************************************************
static void taa_path_clean(
    char* path)
{
    enum
    {
        SEP_SLASH = taa_PATH_SLASH,
        REV_SLASH = (SEP_SLASH == '/') ? '\\' : '/'
    };
    char* pathitr;
    char* ch;

    pathitr = path;
    ch = pathitr;
    while(*ch != '\0')
    {
        if(*ch == '.')
        {
            if(ch[1] == '.')
            {
                int32_t off;
                // Move up to the parent folder
                if(ch == pathitr)
                {
                    // if the '..' sequence is at the beginning of
                    // the pathitr, leave it in place.
                    ch += 2;
                    continue;
                }
                off = ((int32_t) (ch - pathitr)) - 1;
                if(off > 0)
                {
                    --off;
                    if(off > 0 && pathitr[off] == SEP_SLASH)
                    {
                        --off;
                    }
                    while(off > 0 && pathitr[off] != SEP_SLASH)
                    {
                        --off;
                    }
                }
                if(off == 0)
                {
                    ++ch;
                }
                strcpy(pathitr + off, ch + 2);
                ch = pathitr + off;
                continue;
            }
            else if(ch[1] == SEP_SLASH || ch[1] == REV_SLASH)
            {
                // referencing the current folder
                if(ch == pathitr)
                {
                    // if the './' sequence is at the beginning of
                    // the pathitr, leave it in place.
                    ++ch;
                }
                else
                {
                    // move the slash over the period
                    strcpy(ch, ch + 1);
                    // since a slash was moved into this slot,
                    // back up to make sure it's not redundant
                    --ch;
                }
                continue;
            }
        }
        else if(*ch == SEP_SLASH)
        {
            // remove redundant slashes
            if(ch[1] == SEP_SLASH || ch[1] == REV_SLASH)
            {
                strcpy(ch, ch + 1);
                continue;
            }
        }
        else if(*ch == REV_SLASH)
        {
            // convert back slashes to forward slashes.
            *ch = SEP_SLASH;
            continue;
        }
        ++ch;
    }
}

//****************************************************************************
static int32_t taa_path_findextoffset(
    const char* path)
{
    const char* sep = strrchr(path, taa_PATH_SLASH);
    if(sep == NULL)
    {
        sep = path;
    }
    sep = strchr(sep, '.');
    return (sep != NULL) ? ((int32_t) (sep - path)) + 1 : -1;
}

//****************************************************************************
void taa_path_append(
    char* path,
    uint32_t pathsize,
    const char* relpath)
{
    int32_t len;
    char* pos;
    int32_t bufspace;

    len = (int32_t) strlen(path);
    if(len > 0)
    {
        pos = path + len - 1;
        if(*pos != taa_PATH_SLASH)
        {
            ++pos;
            ++len;
            *pos = taa_PATH_SLASH;
        }
        ++pos;
        bufspace = ((int32_t) pathsize) - len - 1;
        if(bufspace > 0)
        {
            strncpy(pos, relpath, bufspace);
        }
        path[pathsize - 1] = '\0';
        taa_path_clean(path);
    }
    else
    {
        taa_path_set(path, pathsize, relpath);
    }
}

//****************************************************************************
void taa_path_getbase(
    const char* path,
    char* baseout,
    uint32_t sz)
{
    const char* sep;
    if(sz > 0)
    {
        int32_t ext;
        sep = strrchr(path, taa_PATH_SLASH);
        if(sep != NULL)
        {
            ++sep;
        }
        else
        {
            // if no separator exists,
            // assume the string is a file name, not a directory name.
            sep = path;
        }
        ext = taa_path_findextoffset(path);
        if(ext >= 0)
        {
            sz = ext;
        }
        strncpy(baseout, sep, sz);
        baseout[sz - 1] = '\0';
    }
}

//****************************************************************************
void taa_path_getdir(
    const char* path,
    char* dirout,
    uint32_t sz)
{
    const char* sep;
    uint32_t end;

    if(sz > 0)
    {
        dirout[0] = '\0';
        sep = strrchr(path, taa_PATH_SLASH);
        if(sep != NULL)
        {
            end = ((uint32_t) (sep - path)) + 1;
            sz = (sz > end) ? end : sz;
            strncpy(dirout, path, sz - 1);
            dirout[sz - 1] = '\0';
        }
    }
}

//****************************************************************************
void taa_path_getext(
    const char* path,
    char* extout,
    uint32_t sz)
{
    if(sz > 0)
    {
        int32_t offset = taa_path_findextoffset(path);
        extout[0] = '\0';
        if(offset >= 0)
        {
            strncpy(extout, path + offset, sz - 1);
            extout[sz - 1] = '\0';
        }
    }
}

//****************************************************************************
void taa_path_getfile(
    const char* path,
    char* fileout,
    uint32_t sz)
{
    const char* sep;
    if(sz > 0)
    {
        sep = strrchr(path, taa_PATH_SLASH);
        if(sep != NULL)
        {
            ++sep;
        }
        else
        {
            // if no separator exists,
            // assume the string is a file name, not a directory name.
            sep = path;
        }
        strncpy(fileout, sep, sz);
        fileout[sz - 1] = '\0';
    }
}

//****************************************************************************
int32_t taa_path_isabsolute(
    const char* path)
{
    int32_t result;
    uint32_t len;

    result = 0; // false
    len = (uint32_t) strlen(path);
    if(len > 0 && path[0] == taa_PATH_SLASH)
    {
        // path begins with a slash
        result = 1; // true
    }
    else if(len > 2 && path[1] == ':' && path[2] == taa_PATH_SLASH)
    {
        // path begins with a msft drive letter
        result = 1; // true
    }
    return result;
}

//****************************************************************************
void taa_path_set(
    char* pathout,
    uint32_t pathsize,
    const char* src)
{
    strncpy(pathout, src, pathsize - 1);
    pathout[pathsize - 1] = '\0';
    taa_path_clean(pathout);
}

//****************************************************************************
void taa_path_setext(
    char* path,
    uint32_t pathsize,
    const char* ext)
{
    int32_t offset = taa_path_findextoffset(path);
    if(offset < 0)
    {
        offset = strlen(path);
        if(((uint32_t) offset) < pathsize)
        {
            path[offset] = '.';
            ++offset;
        }
    }
    if(((uint32_t) offset) < pathsize)
    {
        strncpy(path + offset, ext, pathsize - offset);
    }
    path[pathsize-1] = '\0';
}
