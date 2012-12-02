/**
 * @brief     miscellaneous system function implementation for win32 target
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by system.c
#ifdef taa_SYSTEM_C_
#include <taa/system.h>
#include <assert.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>

struct taa_dir_s
{
    int h;
    const char* first;
    struct _finddata_t data;
};

//****************************************************************************
int taa_chdir(
    const char* path)
{
    return (SetCurrentDirectory(path)) ? 0 : -1;
}

//****************************************************************************
int taa_closedir(
    taa_dir dir)
{
    int err = _findclose(dir->h);
    free(dir);
    return err;
}

//****************************************************************************
char* taa_getcwd(
    char* path_out,
    uint32_t pathsize)
{
    return GetCurrentDirectory(pathsize, path_out) ? path_out : NULL;
}

//****************************************************************************
void* taa_memalign(
    size_t align,
    size_t size)
{
    assert(align > sizeof(uint64_t));
    return _aligned_malloc(size, align);
}

//****************************************************************************
void taa_memalign_free(
    void* p)
{
    _aligned_free(p);
}

//****************************************************************************
int taa_opendir(
    const char* path,
    taa_dir* dir_out)
{
    int result = -1;
    *dir_out = NULL;
    if(path != NULL && *path != '\0')
    {
        char s[256];
        unsigned size = sizeof(s)-3;
        int h;
        struct _finddata_t data;
        strncpy(s, path, size);
        s[size] = '\0';
        size = strlen(s);
        if(s[size-1] == '\\')
        {
            strcpy(s + size, "*");
        }
        else if(s[size-1] != '*')
        {
            strcpy(s + size, "\\*");
        }
        h = _findfirst(s, &data);
        if(h != -1)
        {
            taa_dir dir = (taa_dir) malloc(sizeof(*dir));
            dir->h = h;
            dir->data = data;
            dir->first = dir->data.name;
            *dir_out = dir;
            result = 0;
        }
    }
    return result;
}

//****************************************************************************
const char* taa_readdir(
    taa_dir dir)
{
    const char* s = NULL;
    if(dir->first != NULL)
    {
        s = dir->first;
        dir->first = NULL;
    }
    else if(_findnext(dir->h, &dir->data) != -1)
    {
        s = dir->data.name;
    }
    if(s != NULL)
    {
        while(!strcmp(s, ".") || !strcmp(s, ".."))
        {
            if(_findnext(dir->h, &dir->data) != -1)
            {
                s = dir->data.name;
            }
            else
            {
                s = NULL;
                break;
            }
        }
    }
    return s;
}

//****************************************************************************
void taa_sched_yield()
{
    // This MSDN documentation implies that Sleep(0) will behave more like
    // sched_yield than SwitchToThread and move the thread to the back of the
    // scheduling queue, rather than switching back immediately after the
    // yielded schedule slice has expired.
    //SwitchToThread();
    Sleep(0);
}

//****************************************************************************
void taa_sleep(
    uint32_t ms)
{
    Sleep(ms);
}

//****************************************************************************
int taa_stat(
    const char* path,
    struct taa_stat* st_out)
{
    int result = -1;
    WIN32_FILE_ATTRIBUTE_DATA at;
    if(GetFileAttributesEx(path,GetFileExInfoStandard, &at) != 0)
    {
        uint32_t dirmask = at.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
        uint64_t size = (((uint64_t) at.nFileSizeHigh)<<32) | at.nFileSizeLow;
        st_out->st_mode = (dirmask != 0) ? taa_S_IFDIR : taa_S_IFREG;
        st_out->st_size = (size_t) size;
        result = 0;
    }
    return result;
}

#endif // taa_SYSTEM_C_
