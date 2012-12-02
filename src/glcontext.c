/**
 * @brief     target agnostic render context implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#define taa_GLCONTEXT_C_

#ifndef taa_GL_NULL
#ifdef WIN32
#include "glcontext_win32.c"
#else
#include "glcontext_x11.c"
#endif
#else
#include "glcontext_null.c"
#endif

#undef taa_GLCONTEXT_C_
