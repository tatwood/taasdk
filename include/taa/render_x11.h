/**
 * @brief     rendering header for OpenGL on X11
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_RENDER_X11_H_
#define TAA_RENDER_X11_H_

#include <GL/glx.h>

typedef struct taa_rendercontext_x11_s taa_rendercontext_x11;

struct taa_rendercontext_x11_s
{
    Display* display;
    Window window;
    GLXContext context;
};

struct taa_rendercontext_s
{
    taa_rendercontext_x11 x11;
};

#endif // TAA_RENDER_X11_H_
