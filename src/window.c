/**
 * @brief     target agnostic window management implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#define taa_WINDOW_C_

#ifdef WIN32
#include "window_win32.c"
#else
#include "window_x11.c"
#endif

#undef taa_WINDOW_C_
