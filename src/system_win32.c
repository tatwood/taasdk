/**
 * @brief     miscellaneous system function implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by system.c
#ifdef TAA_SYSTEM_C_

//****************************************************************************
int taa_chdir(
    const char* path)
{
    return (SetCurrentDirectory(path)) ? 0 : -1;
}

//****************************************************************************
void taa_closedir(
    taa_dir* dir)
{
    _findclose(dir->win32.h);
}

//****************************************************************************
char* taa_getcwd(
    char* pathout,
    uint32_t pathsize)
{
    return GetCurrentDirectory(pathsize, pathout) ? pathout : NULL;
}

//****************************************************************************
int taa_getfilestat(
    const char* path,
    taa_filestat* out)
{
    int result = -1;
    WIN32_FILE_ATTRIBUTE_DATA attr;
    if(GetFileAttributesEx(path,GetFileExInfoStandard, &attr) != 0)
    {
        uint32_t dirmask = attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
        out->mode = (dirmask != 0) ? taa_FILE_IFDIR : taa_FILE_IFREG;
        out->size = attr.nFileSizeLow;
        result = 0;
    }
    return result;
}

//****************************************************************************
void taa_getsystemtime(uint64_t* nsout)
{
    static uint64_t freq = 0;
    uint64_t ctr;
    if(freq == 0)
    {
        QueryPerformanceFrequency((LARGE_INTEGER*) &freq);
    }
    QueryPerformanceCounter((LARGE_INTEGER*) &ctr);
    *nsout = (((uint64_t) 1000000000) * ctr)/freq;
}

//****************************************************************************
int taa_opendir(
    const char* path,
    taa_dir* dirout)
{
    dirout->win32.h = -1;
    dirout->win32.name = NULL;
    if(path != NULL && *path != '\0')
    {
        char* s = dirout->win32.data.name;
        uint32_t size = sizeof(dirout->win32.data.name)-3;
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
        dirout->win32.h = _findfirst(s, &dirout->win32.data);
    }
    return (dirout->win32.h != -1) ? 0 : -1;
}

//****************************************************************************
const char* taa_readdir(
    taa_dir* dir)
{
    if(dir->win32.h != -1)
    {
        if(dir->win32.name == NULL)
        {
            dir->win32.name = dir->win32.data.name;
        }
        else if(_findnext(dir->win32.h, &dir->win32.data) == -1)
        {
            dir->win32.name = NULL;
        }
    }
    return dir->win32.name;
}

#endif // TAA_SYSTEM_C_
