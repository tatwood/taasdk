/**
 * @brief     miscellaneous system function implementation for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by system.c
#ifdef taa_SYSTEM_C_
#include <taa/system.h>
#include <assert.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>

//****************************************************************************
int taa_chdir(
    const char* path)
{
    return chdir(path);
}

//****************************************************************************
int taa_closedir(
    taa_dir dir)
{
    return closedir((DIR*) dir);
}

//****************************************************************************
char* taa_getcwd(
    char* path_out,
    uint32_t pathsize)
{
    return getcwd(path_out, pathsize);
}

//****************************************************************************
void* taa_memalign(
    size_t align,
    size_t size)
{
    void* p;
    assert(align > sizeof(uint64_t));  
    if(align <= sizeof(long double))
    {
        // no special alignment necessary    
        p = malloc(size);
    }
    else
    {
        if(posix_memalign(&p, align, size) != 0)
        {
            p = NULL;
        }
    }
    return p;
}

//****************************************************************************
void taa_memalign_free(
    void* p)
{
    free(p);
}

//****************************************************************************
int taa_opendir(
    const char* path,
    taa_dir* dir_out)
{
    DIR* dir = opendir(path);
    *dir_out = (taa_dir) dir;
    return (dir != NULL) ? 0 : -1;
}

//****************************************************************************
const char* taa_readdir(
    taa_dir dir)
{
    struct dirent* entry = readdir((DIR*) dir);
    return (entry != NULL) ? entry->d_name : NULL; 
}

//****************************************************************************
void taa_sched_yield()
{
    sched_yield();
}

//****************************************************************************
void taa_sleep(
    uint32_t ms)
{
    usleep(ms * 1000); // ms to us
}

//****************************************************************************
int taa_stat(
    const char* path,
    struct taa_stat* out)
{
    int result = -1;
    struct stat st;
    if(stat(path, &st) == 0)
    {
        out->st_mode = (st.st_mode & S_IFDIR) ? taa_S_IFDIR : taa_S_IFREG;
        out->st_size = st.st_size;
        result = 0;
    }
    return result;
}

#endif // taa_SYSTEM_C_

