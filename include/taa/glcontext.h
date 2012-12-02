/**
 * @brief     target agnostic render context header
 * @details   This interface is designed to be EGL compatible, even though no
 *            EGL target exists at this point.
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_GLCONTEXT_H_
#define taa_GLCONTEXT_H_

#include "window.h"

#ifdef WIN32
#include "glcontext_win32.h"
#else
#include "glcontext_x11.h"
#endif

//****************************************************************************
// enums

enum taa_glcontext_attrib_e
{
    taa_GLCONTEXT_ALPHA_SIZE   = 0x3021,
    taa_GLCONTEXT_BLUE_SIZE    = 0x3022,
    taa_GLCONTEXT_GREEN_SIZE   = 0x3023,
    taa_GLCONTEXT_RED_SIZE     = 0x3024,
    taa_GLCONTEXT_DEPTH_SIZE   = 0x3025,
    taa_GLCONTEXT_STENCIL_SIZE = 0x3026,
    taa_GLCONTEXT_NONE         = 0x3038
};

//****************************************************************************
// typedefs

typedef enum taa_glcontext_attrib_e taa_glcontext_attrib;

/**
 * @details On EGL, this is an EGLConfig; on X11, this is a
 * ; on win32, it has no meaning.
 */
typedef taa_glcontext_config_target taa_glcontext_config;

/**
 * @details On EGL, this is an EGLDisplay; on X11, this is a
 * (Display*); on win32, it has no meaning.
 */
typedef taa_glcontext_display_target taa_glcontext_display;

/**
 * @details On EGL, this is an EGLSurface; on X11, this is a (Window) or
 * (Pixmap); on win32, it is a (HDC).
 */
typedef taa_glcontext_surface_target taa_glcontext_surface;

/**
 * @details On EGL, this is an EGLContext; on X11, this is a (GLXContext); 
 * On win32, it is a (HGLRC).
 */
typedef taa_glcontext_target taa_glcontext;

//***************************************************************************
// functions

/**
 * @return 1 on success, 0 on failure
 */
taa_SDK_LINKAGE int taa_glcontext_choose_config(
    taa_glcontext_display disp,
    const int* attribs,
    taa_glcontext_config* configs_out,
    int configssize,
    int* numconfigs_out);

taa_SDK_LINKAGE taa_glcontext taa_glcontext_create(
    taa_glcontext_display disp,
    taa_glcontext_surface surface,
    taa_glcontext_config config,
    taa_glcontext shared,
    const int* attribs);

taa_SDK_LINKAGE taa_glcontext_surface taa_glcontext_create_surface(
    taa_glcontext_display disp,
    taa_glcontext_config config,
    taa_window win);

/**
 * @return 1 on success, 0 on failure
 */
taa_SDK_LINKAGE int taa_glcontext_destroy(
    taa_glcontext_display disp,
    taa_glcontext ctx);

/**
 * @return 1 on success, 0 on failure
 */
taa_SDK_LINKAGE int taa_glcontext_destroy_surface(
    taa_glcontext_display disp,
    taa_window win,
    taa_glcontext_surface surface);

taa_SDK_LINKAGE taa_glcontext_display taa_glcontext_get_display(
    taa_window_display windisp);

/**
 * @return 1 on success, 0 on failure
 */
taa_SDK_LINKAGE int taa_glcontext_initialize(
    taa_glcontext_display disp);

/**
 * @return 1 on success, 0 on failure
 */
taa_SDK_LINKAGE int taa_glcontext_make_current(
    taa_glcontext_display disp,
    taa_glcontext_surface surface,
    taa_glcontext ctx);

/**
 * @return 1 on success, 0 on failure
 */
taa_SDK_LINKAGE int taa_glcontext_swap_buffers(
    taa_glcontext_display disp,
    taa_glcontext_surface surface);

/**
 * @return 1 on success, 0 on failure
 */
taa_SDK_LINKAGE int taa_glcontext_swap_interval(
    taa_glcontext_display disp,
    taa_glcontext_surface surface,
    int interval);
/**
 * @return 1 on success, 0 on failure
 */
taa_SDK_LINKAGE int taa_glcontext_terminate(
    taa_glcontext_display disp);

#endif // taa_GLCONTEXT_H_
