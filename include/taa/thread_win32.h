/**
 * @brief     thread management header for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_THREAD_WIN32_H_
#define TAA_THREAD_WIN32_H_

typedef struct taa_threadwin32_s taa_threadwin32;

struct taa_threadwin32_s
{
    HANDLE h;
    uint32_t id;
};

struct taa_thread_s
{
     taa_threadwin32 win32;
};

#endif // TAA_THREAD_WIN32_H_

