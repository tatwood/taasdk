/**
 * @brief     rendering implementation for OpenGL on X11
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by render.c
#ifdef TAA_RENDER_C_

#include <taa/error.h>
#include <taa/thread.h>
#include <stdlib.h>

//****************************************************************************
void taa_rendercontext_choosevisualinfo(
    taa_window_display* disp,
    taa_window_visualinfo* viout)
{
    int32_t attrlist[] =
    {
        GLX_RGBA,
        GLX_DOUBLEBUFFER,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        GLX_STENCIL_SIZE, 8,
        None
    };
    XVisualInfo* xvi;
    xvi = glXChooseVisual(disp->x11.display, disp->x11.screen, attrlist);
    viout->x11.visual = xvi->visual;
    taa_CHECK_ERROR(viout->x11.visual != NULL, "invalid X Visual")
}

//****************************************************************************
void taa_rendercontext_create(
    taa_window* win,
    taa_rendercontext* rcout)
{
    int32_t n;
    XWindowAttributes xattr;
    XVisualInfo v;
    XVisualInfo* vi;

    rcout->x11.display = win->x11.display;
    rcout->x11.window = win->x11.window;

    XGetWindowAttributes(rcout->x11.display, rcout->x11.window, &xattr);

    v.screen = XScreenNumberOfScreen(xattr.screen);
    v.visualid = XVisualIDFromVisual(xattr.visual);
    vi = XGetVisualInfo(
        rcout->x11.display,
        VisualScreenMask|VisualIDMask,
        &v,
        &n);
    taa_CHECK_ERROR(vi != NULL, "invalid GLX VisualInfo");

    // create the GL context
    rcout->x11.context = glXCreateContext(rcout->x11.display,vi,NULL,GL_TRUE);
}

//****************************************************************************
void taa_rendercontext_createshared(
    taa_rendercontext* rcparent,
    taa_rendercontext* rcout)
{
    GLXContext glcp = rcparent->x11.context;
    int32_t n;
    XWindowAttributes xattr;
    XVisualInfo v;
    XVisualInfo* vi;

    rcout->x11.display = rcparent->x11.display;
    rcout->x11.window = rcparent->x11.window;

    XGetWindowAttributes(rcout->x11.display, rcout->x11.window, &xattr);

    v.screen = XScreenNumberOfScreen(xattr.screen);
    v.visualid = XVisualIDFromVisual(xattr.visual);
    vi = XGetVisualInfo(
        rcout->x11.display,
        VisualScreenMask|VisualIDMask,
        &v,
        &n);
    taa_CHECK_ERROR(vi != NULL, "invalid GLX VisualInfo");

    // create the GL context
    rcout->x11.context = glXCreateContext(rcout->x11.display,vi,glcp,GL_TRUE);
}

//****************************************************************************
void taa_rendercontext_destroy(
    taa_rendercontext* rc)
{
    glXDestroyContext(rc->x11.display, rc->x11.context);
}

//****************************************************************************
void taa_rendercontext_makecurrent(
    taa_window_display* disp,
    taa_rendercontext* rc)
{
    if(rc != NULL)
    {
        static volatile int32_t s_initonce = 0;

        // connect the context to the window
        glXMakeCurrent(disp->x11.display, rc->x11.window, rc->x11.context);
        taa_render_checkerrors();
        if(s_initonce != 2)
        {
            // init glew
            if(taa_ATOMIC_CMPXCHG32(&s_initonce, 0, 1) == 0)
            {
                // first thread in
#ifndef taa_RENDER_GL11 // glew not required for OpenGL 1.1
                glewInit();
#endif
                s_initonce = 2; // done!
#ifndef NDEBUG
printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
printf("GL_VERSION = %s\n", glGetString(GL_VERSION));
printf("GL_EXTENSIONS = %s\n\n", glGetString(GL_EXTENSIONS));
#endif
            }
            else
            {
                // another thread already begain initialization
                while(s_initonce != 2)
                {
                    taa_thread_yield(); // wait for it to complete
                }
            }
        }
    }
    else
    {
        glXMakeCurrent(disp->x11.display, None, NULL);
    }
}

//****************************************************************************
void taa_rendercontext_swapbuffers(
    taa_rendercontext* rc)
{
    glXSwapBuffers(rc->x11.display, rc->x11.window);
    taa_render_checkerrors();
}

#endif // TAA_RENDER_C_
