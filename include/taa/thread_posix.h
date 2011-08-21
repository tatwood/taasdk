/**
 * @brief     thread management header for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_THREAD_POSIX_H_
#define TAA_THREAD_POSIX_H_

#include <pthread.h>

struct taa_thread_s
{
    pthread_t posix;
};

#endif // TAA_THREAD_POSIX_H_
