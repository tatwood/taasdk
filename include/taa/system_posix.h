/**
 * @brief     miscellaneous system function header for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SYSTEM_POSIX_H_
#define taa_SYSTEM_POSIX_H_

#include <dirent.h>
#include <sys/stat.h>

enum
{
    taa_S_IFREG_TARGET = S_IFREG, 
    taa_S_IFDIR_TARGET = S_IFDIR
};

typedef struct taa_dir_posix_s taa_dir_posix;

struct taa_dir_posix_s
{
    DIR *dir;
};

struct taa_dir_s
{
    taa_dir_posix posix;
};

#endif // taa_SYSTEM_POSIX_H_
