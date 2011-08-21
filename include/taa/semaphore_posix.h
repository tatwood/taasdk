/**
 * @brief     semaphore management header for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_SEMAPHORE_POSIX_H_
#define TAA_SEMAPHORE_POSIX_H_

#include <semaphore.h>

struct taa_semaphore_s
{
    sem_t posix;
};

#endif // TAA_SEMAPHORE_POSIX_H_
