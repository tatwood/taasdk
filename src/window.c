/**
 * @brief     target agnostic window management implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/window.h>

#define TAA_WINDOW_C_

#ifdef WIN32
#include "window_win32.c"
#else
#include "window_x11.c"
#endif

#undef TAA_WINDOW_C_
