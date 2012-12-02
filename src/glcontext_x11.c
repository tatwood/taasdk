/**
 * @brief     render context implementation for OpenGL on X11
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifdef taa_GLCONTEXT_C_
#include <taa/glcontext.h>
#include <taa/gl.h>
#include <GL/glx.h>
#include <assert.h>

//****************************************************************************
int taa_glcontext_choose_config(
    taa_glcontext_display disp,
    const int* attribs,
    taa_glcontext_config* configs_out,
    int configssize,
    int* numconfigs_out)
{
    int xattribs[3 + 0x3042 - 0x3020]; // range of egl attributes;
    XVisualInfo* vi = NULL;
    int success = 0;
    int i = 0;
    do
    {
        switch(attribs[i])
        {
        case taa_GLCONTEXT_ALPHA_SIZE:
            xattribs[i  ] = GLX_ALPHA_SIZE;
            xattribs[i+1] = attribs[i+1]; 
            break;
        case taa_GLCONTEXT_BLUE_SIZE:
            xattribs[i  ] = GLX_BLUE_SIZE;
            xattribs[i+1] = attribs[i+1]; 
            break;
        case taa_GLCONTEXT_GREEN_SIZE:
            xattribs[i  ] = GLX_GREEN_SIZE;
            xattribs[i+1] = attribs[i+1]; 
            break;
        case taa_GLCONTEXT_RED_SIZE:
            xattribs[i  ] = GLX_RED_SIZE;
            xattribs[i+1] = attribs[i+1]; 
            break;
        case taa_GLCONTEXT_DEPTH_SIZE:
            xattribs[i  ] = GLX_DEPTH_SIZE;
            xattribs[i+1] = attribs[i+1];
            break; 
        case taa_GLCONTEXT_STENCIL_SIZE:
            xattribs[i  ] = GLX_STENCIL_SIZE;
            xattribs[i+1] = attribs[i+1];
            break;
        }
        i += 2;
    }
    while(attribs[i] != taa_GLCONTEXT_NONE);
    xattribs[i    ] = GLX_RGBA;
    xattribs[i + 1] = GLX_DOUBLEBUFFER;
    xattribs[i + 2] = None;
    vi = glXChooseVisual(disp, XDefaultScreen(disp), xattribs);
    if(vi != NULL && configssize >= 1)
    {
        *configs_out = vi;
        success = 1;
    }
    *numconfigs_out = success;
    return success;
}

//****************************************************************************
taa_glcontext taa_glcontext_create(
    taa_glcontext_display disp,
    taa_glcontext_surface surface,
    taa_glcontext_config config,
    taa_glcontext shared,
    const int* attribs)
{
    return glXCreateContext(disp, config, shared, GL_TRUE);
}

//****************************************************************************
taa_glcontext_surface taa_glcontext_create_surface(
    taa_glcontext_display disp,
    taa_glcontext_config config,
    taa_window win)
{
    return win;
}

//****************************************************************************
int taa_glcontext_destroy(
    taa_glcontext_display disp,
    taa_glcontext ctx)
{
    glXDestroyContext(disp, ctx);
    return 1;
}

//****************************************************************************
int taa_glcontext_destroy_surface(
    taa_glcontext_display disp,
    taa_window win,
    taa_glcontext_surface surface)
{
    return 1;
}

//****************************************************************************
taa_glcontext_display taa_glcontext_get_display(
    taa_window_display windisp)
{
    return windisp;
}

//****************************************************************************
int taa_glcontext_initialize(
    taa_glcontext_display disp)
{
    return 1;
}

//****************************************************************************
int taa_glcontext_make_current(
    taa_glcontext_display disp,
    taa_glcontext_surface surface,
    taa_glcontext ctx)
{
    return glXMakeCurrent(disp, surface, ctx);
}

//****************************************************************************
int taa_glcontext_swap_buffers(
    taa_glcontext_display disp,
    taa_glcontext_surface surface)
{
    glXSwapBuffers(disp, surface);
    assert(taa_gl_get_error() == 0);
    return 1;
}

//****************************************************************************
int taa_glcontext_swap_interval(
    taa_glcontext_display disp,
    taa_glcontext_surface surface,
    int interval)
{
    static int (*s_glXSwapIntervalEXT)(Display*, GLXDrawable, int);
    int result = 0;
    if(s_glXSwapIntervalEXT == NULL)
    {
        s_glXSwapIntervalEXT = (int (*)(Display*, GLXDrawable, int))
            glXGetProcAddress((const GLubyte *) "glXSwapIntervalEXT");
    }
    if(s_glXSwapIntervalEXT != NULL)
    {
        result = s_glXSwapIntervalEXT(disp, surface, interval);
    }
    return result;
}

//****************************************************************************
int taa_glcontext_terminate(
    taa_glcontext_display disp)
{
    return 1;
}

#endif // taa_GLCONTEXT_C_
