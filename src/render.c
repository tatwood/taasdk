/**
 * @brief     target agnostic rendering implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/render.h>

#define TAA_RENDER_C_

#if taa_RENDER_GL11
#ifdef WIN32
#include "render_win32.c"
#else
#include "render_x11.c"
#endif
#include "render_gl11.c"
#elif taa_RENDER_NULL
// do nothing
#else
#error render mode not supported
#endif

#undef TAA_RENDER_C_
