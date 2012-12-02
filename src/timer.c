/**
 * @brief     target agnostic timer implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#define taa_TIMER_C_

#ifdef WIN32
#include "timer_win32.c"
#else
#include "timer_posix.c"
#endif

#undef taa_TIMER_C_
