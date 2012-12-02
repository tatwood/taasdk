/**
 * @brief     target agnostic mutex implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#define taa_MUTEX_C_

#ifdef WIN32
#include "mutex_win32.c"
#else
#include "mutex_posix.c"
#endif

#undef taa_MUTEX_C_
