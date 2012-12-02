/**
 * @brief     target agnostic keyboard input implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#define taa_KEYBOARD_C_

#ifdef WIN32
#include "keyboard_win32.c"
#else
#include "keyboard_x11.c"
#endif

#undef taa_KEYBOARD_C_
