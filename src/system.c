/**
 * @brief     target agnostic implementation of miscellaneous system functions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/system.h>

#define TAA_SYSTEM_C_

#ifdef WIN32
#include "system_win32.c"
#else
#include "system_posix.c"
#endif

#undef TAA_SYSTEM_C_
