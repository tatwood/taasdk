/**
 * @brief     miscellaneous system function header for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_SYSTEM_POSIX_H_
#define TAA_SYSTEM_POSIX_H_

#include <dirent.h>

typedef struct taa_dir_posix_s taa_dir_posix;

struct taa_dir_posix_s
{
    DIR *dir;
};

struct taa_dir_s
{
    taa_dir_posix posix;
};

#endif // TAA_SYSTEM_POSIX_H_

