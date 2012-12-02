/**
 * @brief     path string handling implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/path.h>
#include <string.h>

//****************************************************************************
void taa_path_clean(
    char* path,
    char sepslash)
{
    char revslash = (sepslash == '/') ? '\\' : '/';
    char* ch;
    char* end;
    end = path + strlen(path) + 1; // include space for NULL terminator

    // pass 0: convert all slashes to native value
    ch = path;
    while(*ch != '\0')
    {    
        if(*ch == revslash)
        {
            *ch = sepslash;
        }
        ++ch;
    }    
    // pass 1: flatten redirections to parent dir (../)
    ch = path;
    while(*ch != '\0')
    {
        if(*ch == '.')
        {
            if(ch[1] == '.')
            {
                int32_t off;
                if(ch == path)
                {
                    // if the '..' sequence is at the beginning of
                    // the path, leave it in place.
                    ch += 2;
                    continue;
                }
                off = ((int32_t) (ch - path)) - 1;
                // find the beginning of the dir preceeding the '..'
                if(off > 0)
                {
                    --off;
                    if(off > 0 && path[off] == sepslash)
                    {
                        --off;
                    }
                    while(off > 0 && path[off] != sepslash)
                    {
                        --off;
                    }
                }
                if(off == 0 && path[off] == '.')
                {
                    // never remove a '.' from the front of the path
                    ch += 2;
                    continue;
                }
                if(path[off+1] == '.' && path[off+2] == '.')
                {
                    // if the preceeding dir is a '..' sequence, 
                    // then leave it in place.
                    ch += 2;
                    continue;
                }
                // if the dir being removed is at the beginning of a
                // relative path, then the full '../' needs to be removed to
                // prevent the path from becoming absolute.
                if(off == 0)
                {
                    ++ch;
                }             
                // remove the '..' and the dir preceeding it
                end -= 2;
                memmove(path + off, ch + 2, (size_t) (end - ch));
                ch = path + off;
                continue;
            }
        }
        else if(*ch == sepslash)
        {
            // remove redundant slashes
            if(ch[1] == sepslash)
            {
                --end;
                memmove(ch, ch + 1, (size_t) (end - ch));
                continue;
            }
        }
        ++ch;
    }
    // pass 2: remove self referencing dirs (./)
    ch = path;
    while(*ch != '\0')
    {
        if(*ch == '.')
        {
            if(ch == path)
            {
                // never remove a '.' from the front of the path
                ++ch;
            }        
            else if(ch[1] == '.')
            {
                // preserve any remaining instances of '..'
                ch += 2;
                continue;
            }        
            else if(ch[1] == sepslash)
            {
                // move the slash over the period
                --end;
                memmove(ch, ch + 1, (size_t) (end - ch));
                // since a slash was moved into this slot,
                // back up to make sure it's not redundant
                --ch;
                continue;
            }
        }
        else if(*ch == sepslash)
        {
            // remove redundant slashes
            if(ch[1] == sepslash)
            {
                --end;
                memmove(ch, ch + 1, (size_t) (end - ch));
                continue;
            }
        }        
        ++ch;
    }    
}

//****************************************************************************
static const char* taa_path_find_last_slash(
    const char* path)
{
    const char* slash = strrchr(path, taa_PATH_SLASH);
    if(taa_PATH_SLASH != '/')
    {
        // on win32, slashes may exist in either direction
        const char* fwdslash = strrchr(path, '/');
        if(fwdslash > slash)
        {
            slash = fwdslash;
        }
    }
    return slash;
}

//****************************************************************************
static int taa_path_find_ext_offset(
    const char* path)
{
    const char* sep = taa_path_find_last_slash(path);
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
        taa_path_clean(path, taa_PATH_SLASH);
    }
    else
    {
        taa_path_set(path, pathsize, relpath);
    }
}

//****************************************************************************
void taa_path_get_base(
    const char* path,
    char* base_out,
    uint32_t sz)
{
    const char* sep;
    if(sz > 0)
    {
        int32_t ext;
        sep = taa_path_find_last_slash(path);
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
        ext = taa_path_find_ext_offset(path);
        if(ext >= 0)
        {
            sz = ext;
        }
        strncpy(base_out, sep, sz);
        base_out[sz - 1] = '\0';
    }
}

//****************************************************************************
void taa_path_get_dir(
    const char* path,
    char* dir_out,
    uint32_t sz)
{
    const char* sep;
    uint32_t end;

    if(sz > 0)
    {
        dir_out[0] = '\0';
        sep = taa_path_find_last_slash(path);
        if(sep != NULL)
        {
            end = ((uint32_t) (sep - path)) + 1;
            sz = (sz > end) ? end : sz;
            strncpy(dir_out, path, sz - 1);
            dir_out[sz - 1] = '\0';
        }
    }
}

//****************************************************************************
void taa_path_get_ext(
    const char* path,
    char* ext_out,
    uint32_t sz)
{
    if(sz > 0)
    {
        int32_t offset = taa_path_find_ext_offset(path);
        ext_out[0] = '\0';
        if(offset >= 0)
        {
            strncpy(ext_out, path + offset, sz - 1);
            ext_out[sz - 1] = '\0';
        }
    }
}

//****************************************************************************
void taa_path_get_file(
    const char* path,
    char* file_out,
    uint32_t sz)
{
    const char* sep;
    if(sz > 0)
    {
        sep = taa_path_find_last_slash(path);
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
        strncpy(file_out, sep, sz);
        file_out[sz - 1] = '\0';
    }
}

//****************************************************************************
int32_t taa_path_is_absolute(
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
    char* path,
    uint32_t pathsize,
    const char* src)
{
    strncpy(path, src, pathsize - 1);
    path[pathsize - 1] = '\0';
    taa_path_clean(path, taa_PATH_SLASH);
}

//****************************************************************************
void taa_path_set_ext(
    char* path,
    uint32_t pathsize,
    const char* ext)
{
    int32_t offset = taa_path_find_ext_offset(path);
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
