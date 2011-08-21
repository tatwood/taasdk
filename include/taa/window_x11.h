/**
 * @brief     window management header for X11
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_WINDOW_X11_H_
#define TAA_WINDOW_X11_H_

#include <X11/X.h>
#include <X11/Xlib.h>

typedef struct taa_window_display_x11_s taa_window_display_x11;
typedef struct taa_window_visualinfo_x11_s taa_window_visualinfo_x11;
typedef struct taa_window_x11_s taa_window_x11;

struct taa_window_display_x11_s
{
    Display* display;
    int32_t screen;
};

struct taa_window_visualinfo_x11_s
{
    Visual* visual;
};

struct taa_window_x11_s
{
    Display* display;
    Colormap colormap;
    Window window;
    Atom wmdelete;
    taa_window_state* state;
};

struct taa_window_display_s
{
    taa_window_display_x11 x11;
};

struct taa_window_visualinfo_s
{
    taa_window_visualinfo_x11 x11;
};

struct taa_window_s
{
    taa_window_x11 x11;
};

#endif // TAA_WINDOW_X11_H_
