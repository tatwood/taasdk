/**
 * @brief     target agnostic mouse input implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#define taa_MOUSE_C_

#ifdef WIN32
#include "mouse_win32.c"
#else
#include "mouse_x11.c"
#endif

#undef taa_MOUSE_C_
