/**
 * @brief     miscellaneous system function implementation for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by system.c
#ifdef TAA_SYSTEM_C_

#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

//****************************************************************************
int taa_chdir(
    const char* path)
{
    return chdir(path);
}

//****************************************************************************
void taa_closedir(
    taa_dir* dir)
{
    closedir(dir->posix.dir);
}

//****************************************************************************
char* taa_getcwd(
    char* pathout,
    uint32_t pathsize)
{
    return getcwd(pathout, pathsize);
}

//****************************************************************************
int taa_getfilestat(
    const char* path,
    taa_filestat* out)
{
    int result = -1;
    struct stat st;
    if(stat(path, &st) == 0)
    {
        out->mode = (st.st_mode&S_IFDIR) ? taa_FILE_IFDIR : taa_FILE_IFREG;
        out->size = st.st_size;
        result = 0;
    }
    return result;
}

//****************************************************************************
void taa_getsystemtime(uint64_t* nsout)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    *nsout = ((uint64_t) ts.tv_sec)*1000000000L + ts.tv_nsec;
}

//****************************************************************************
int taa_opendir(
    const char* path,
    taa_dir* dirout)
{
    dirout->posix.dir = opendir(path);
    return (dirout->posix.dir != NULL) ? 0 : -1;
}

//****************************************************************************
const char* taa_readdir(
    taa_dir* dir)
{
    struct dirent* entry = readdir(dir->posix.dir);
    return (entry != NULL) ? entry->d_name : NULL; 
}

#endif // TAA_SYSTEM_C_

