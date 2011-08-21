/**
 * @brief     rendering implementation for OpenGL on win32
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
    taa_window_display* display,
    taa_window_visualinfo* viout)
{
    viout->win32 = 0;
}

//****************************************************************************
void taa_rendercontext_create(
    taa_window* win,
    taa_rendercontext* rcout)
{
    PIXELFORMATDESCRIPTOR pfd;
    int32_t pf;
    int32_t r;

    rcout->win32.hwnd = win->win32.hwnd;
    rcout->win32.hdc = GetDC(rcout->win32.hwnd);
    SwapBuffers(rcout->win32.hdc); // required or create RC may fail

    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    // choose pixel format
    pf = ChoosePixelFormat(rcout->win32.hdc, &pfd);
    taa_CHECK_ERROR1(pf != 0, "ChoosePixelFormat() failed: %u",GetLastError());

    // set pixel format
    r = SetPixelFormat(rcout->win32.hdc, pf, &pfd);
    taa_CHECK_ERROR1(r != 0, "SetPixelFormat() failed: %u",GetLastError());

    // create context
    rcout->win32.hglrc = wglCreateContext(rcout->win32.hdc);
    r = rcout->win32.hglrc != NULL;
    taa_CHECK_ERROR1(r != 0, "wglCreateContext() failed: %u",GetLastError());
}

//****************************************************************************
void taa_rendercontext_createshared(
    taa_rendercontext* rcparent,
    taa_rendercontext* rcout)
{
    PIXELFORMATDESCRIPTOR pfd;
    int32_t pf;
    int32_t r;
    rcout->win32.hwnd = rcparent->win32.hwnd;
    rcout->win32.hdc = GetDC(rcout->win32.hwnd);
    SwapBuffers(rcout->win32.hdc); // required or create RC may fail

    pf = GetPixelFormat(rcparent->win32.hdc);
    taa_CHECK_ERROR1(pf != 0, "GetPixelFormat() failed: %u",GetLastError());

    r = DescribePixelFormat(rcparent->win32.hdc,pf,sizeof(pfd),&pfd);
    taa_CHECK_ERROR1(r != 0,"DescribePixelFormat() failed: %u",GetLastError());

    // set pixel format
    r = SetPixelFormat(rcout->win32.hdc, pf, &pfd);
    taa_CHECK_ERROR1(r != 0, "SetPixelFormat() failed: %u",GetLastError());

    // create context
    rcout->win32.hglrc = wglCreateContext(rcout->win32.hdc);
    r = rcout->win32.hglrc != NULL;
    taa_CHECK_ERROR1(r != 0, "wglCreateContext() failed: %u",GetLastError());

    // share lists
    r = wglShareLists(rcparent->win32.hglrc, rcout->win32.hglrc);
    taa_CHECK_ERROR1(r != 0, "wglShareLists() failed: %u",GetLastError());
}

//****************************************************************************
void taa_rendercontext_destroy(
    taa_rendercontext* rc)
{
    if(rc->win32.hwnd != NULL && rc->win32.hdc != NULL)
    {
        ReleaseDC(rc->win32.hwnd, rc->win32.hdc);
    }
    if(rc->win32.hglrc != NULL)
    {
        wglDeleteContext(rc->win32.hglrc);
    }
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
        wglMakeCurrent(rc->win32.hdc, rc->win32.hglrc);
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
        wglMakeCurrent(NULL, NULL);
    }
}

//****************************************************************************
void taa_rendercontext_swapbuffers(
    taa_rendercontext* rc)
{
    SwapBuffers(rc->win32.hdc);
    taa_render_checkerrors();
}

#endif // TAA_RENDER_C_
