/**
 * @brief     render context implementation for OpenGL on win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifdef taa_GLCONTEXT_C_
#include <taa/glcontext.h>
#include <taa/gl.h>
#include <assert.h>
#include <string.h>

static void taa_glcontext_convert_attribs(
    const int* attribs,
    PIXELFORMATDESCRIPTOR* pfd_out)
{
    int i = 0;
    memset(pfd_out, 0, sizeof(*pfd_out));
    pfd_out->nSize = sizeof(*pfd_out);
    pfd_out->nVersion = 1;
    pfd_out->dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
    pfd_out->iLayerType = PFD_MAIN_PLANE;
    do
    {
        switch(attribs[i])
        {
        case taa_GLCONTEXT_ALPHA_SIZE:
            pfd_out->cAlphaBits = attribs[i + 1];
            break;
        case taa_GLCONTEXT_BLUE_SIZE:
            pfd_out->cBlueBits = attribs[i + 1];
            break;
        case taa_GLCONTEXT_GREEN_SIZE:
            pfd_out->cGreenBits = attribs[i + 1];
            break;
        case taa_GLCONTEXT_RED_SIZE:
            pfd_out->cRedBits = attribs[i + 1];
            break;
        case taa_GLCONTEXT_DEPTH_SIZE:
            pfd_out->cDepthBits = attribs[i+1];
            break; 
        case taa_GLCONTEXT_STENCIL_SIZE:
            pfd_out->cStencilBits = attribs[i+1];
            break;
        }
        i += 2;
    }
    while(attribs[i] != taa_GLCONTEXT_NONE);
}

//****************************************************************************
int taa_glcontext_choose_config(
    taa_glcontext_display disp,
    const int* attribs,
    taa_glcontext_config* configs_out,
    int configssize,
    int* numconfigs_out)
{  
    int success;
    success = 0;
    if(configssize > 0)
    {
        HDC hdc;
        PIXELFORMATDESCRIPTOR pfd;
        int pf;
        hdc = GetDC(NULL);
        taa_glcontext_convert_attribs(attribs, &pfd);
        pf = ChoosePixelFormat(hdc, &pfd);
        ReleaseDC(NULL, hdc);
        if(pf != 0)
        {
            *configs_out = pf;
            *numconfigs_out = 1;
            success = 1;
        }
    }
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
    HGLRC rc = NULL;
    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(surface, config, sizeof(pfd), &pfd);
    // set pixel format
    if(SetPixelFormat(surface, config, &pfd) != 0)
    {
        // create context
        rc = wglCreateContext(surface);
    }
    if(rc != NULL && shared != NULL)
    {
        // share lists
        wglShareLists((HGLRC) shared, rc);
    }
    return rc;
}

//****************************************************************************
taa_glcontext_surface taa_glcontext_create_surface(
    taa_glcontext_display disp,
    taa_glcontext_config config,
    taa_window win)
{
    return GetDC(win);
}

//****************************************************************************
int taa_glcontext_destroy(
    taa_glcontext_display disp,
    taa_glcontext ctx)
{
    wglDeleteContext((HGLRC) ctx);
    return 1;
}

//****************************************************************************
int taa_glcontext_destroy_surface(
    taa_glcontext_display disp,
    taa_window win,
    taa_glcontext_surface surface)
{
    ReleaseDC(win, surface);
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
    return wglMakeCurrent(surface, (HGLRC) ctx);
}

//****************************************************************************
int taa_glcontext_swap_buffers(
    taa_glcontext_display disp,
    taa_glcontext_surface surface)
{
    SwapBuffers(surface);
    assert(taa_gl_get_error() == 0);
    return 1;
}

//****************************************************************************
int taa_glcontext_swap_interval(
    taa_glcontext_display disp,
    taa_glcontext_surface surface,
    int interval)
{
    static BOOL (WINAPI *s_wglSwapIntervalEXT)(int);
    int result = 0;
    if(s_wglSwapIntervalEXT == NULL)
    {
        s_wglSwapIntervalEXT = (BOOL (WINAPI*)(int))
            wglGetProcAddress((const GLubyte *) "wglSwapIntervalEXT");
    }
    if(s_wglSwapIntervalEXT != NULL)
    {
        result = s_wglSwapIntervalEXT(interval);
    }
    return result;
}

//****************************************************************************
int taa_glcontext_terminate(
    taa_glcontext_display disp)
{
    return 1;
}

#endif taa_GLCONTEXT_C_
