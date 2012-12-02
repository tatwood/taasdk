/**
 * @brief     target agnostic futex implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#define taa_FUTEX_C_

#ifdef WIN32
#include "futex_win32.c"
#else
#include "futex_posix.c"
#endif

#undef taa_FUTEX_C_
