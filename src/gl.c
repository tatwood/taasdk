/**
 * @brief     target agnostic rendering implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#define taa_GL_C_

#ifdef taa_GL_NULL
#include "gl_null.c"
#elif defined(taa_GL_21) || defined(taa_GL_ES2)
#include "gl_21.c"
#else
#include "gl_11.c"
#endif

#undef taa_GL_C_
