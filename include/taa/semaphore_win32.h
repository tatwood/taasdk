/**
 * @brief     semaphore management header for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_SEMAPHORE_WIN32_H_
#define TAA_SEMAPHORE_WIN32_H_

struct taa_semaphore_s
{
    HANDLE win32;
};

#endif // TAA_SEMAPHORE_WIN32_H_
