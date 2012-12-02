/**
 * @brief     render context implementation for null device
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifdef taa_GLCONTEXT_C_
#include <taa/glcontext.h>

//****************************************************************************
int taa_glcontext_choose_config(
    taa_glcontext_display disp,
    const taa_glcontext_attrib* attribs,
    taa_glcontext_config* configs_out,
    int configssize,
    int* numconfigs_out)
{
    int success = 0;
    if(configsize >= 1)
    {
        *configs_out = 0;
        success = 1;
    }
    *numconfigs_out = success;
    return success;
}

//****************************************************************************
taa_glcontext taa_glcontext_create(
    taa_glcontext_display disp,
    taa_glcontext_config config,
    taa_glcontext shared,
    const taa_glcontext_attrib* attribs)
{
    return disp;
}

//****************************************************************************
taa_glcontext_surface taa_glcontext_create_surface(
    taa_glcontext_display disp,
    taa_glcontext_config config,
    taa_window win,
    taa_glcontext_attrib* attribs)
{
    return disp;
}

//****************************************************************************
int taa_glcontext_destroy(
    taa_glcontext_display disp,
    taa_glcontext ctx)
{
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
    return 1;
}

//****************************************************************************
int taa_glcontext_swap_buffers(
    taa_glcontext_display disp,
    taa_glcontext_surface surface)
{
    return 1;
}

//****************************************************************************
int taa_glcontext_swap_interval(
    taa_glcontext_display disp,
    int interval)
{
    return 1;
}

//****************************************************************************
int taa_glcontext_terminate(
    taa_glcontext_display disp)
{
    return 1;
}

#endif taa_GLCONTEXT_C_

