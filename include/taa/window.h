/**
 * @brief     target agnostic window management header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_WINDOW_H_
#define taa_WINDOW_H_

#include "system.h"

#ifdef WIN32
#include "window_win32.h"
#else
#include "window_x11.h"
#endif

//****************************************************************************
// enums

enum
{
    taa_WINDOW_BORDERLESS = (1 << 0),
    taa_WINDOW_FULLSCREEN = (1 << 1)
};

enum taa_window_eventtype_e
{
    taa_WINDOW_EVENT_ACTIVATE,
    taa_WINDOW_EVENT_CLOSE,
    taa_WINDOW_EVENT_DEACTIVATE,
    taa_WINDOW_EVENT_KEY_DOWN,
    taa_WINDOW_EVENT_KEY_UP,
    taa_WINDOW_EVENT_MOUSE_BUTTON1_DOWN,
    taa_WINDOW_EVENT_MOUSE_BUTTON1_UP,
    taa_WINDOW_EVENT_MOUSE_BUTTON2_DOWN,
    taa_WINDOW_EVENT_MOUSE_BUTTON2_UP,
    taa_WINDOW_EVENT_MOUSE_BUTTON3_DOWN,
    taa_WINDOW_EVENT_MOUSE_BUTTON3_UP,
    taa_WINDOW_EVENT_MOUSE_MOVE,
    taa_WINDOW_EVENT_SIZE
};

//****************************************************************************
// typedefs

typedef enum taa_window_eventtype_e taa_window_eventtype;

typedef union taa_window_event_u taa_window_event;

/**
 * @details On X11, this is a (Display*); on win32, it has no meaning.
 */
typedef taa_window_display_target taa_window_display;

/**
 * @details On X11, this is a (Window); on win32, it is a (HWND).
 */
typedef taa_window_target taa_window;

//****************************************************************************
// structs

union taa_window_event_u
{
    taa_window_eventtype type;
    struct
    {
        taa_window_eventtype type;
        uint8_t keycode;
        char ascii;
    } key;
    struct
    {
        taa_window_eventtype type;
        int32_t cursorx;
        int32_t cursory;
        int8_t button1;
        int8_t button2;
        int8_t button3;
    } mouse;
    struct
    {
        taa_window_eventtype type;
        uint32_t width;
        uint32_t height;
    } size;
};

//****************************************************************************
// functions

taa_SDK_LINKAGE void taa_window_close_display(
    taa_window_display disp);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_window_create(
    taa_window_display disp,
    const char* title,
    unsigned int width,
    unsigned int height,
    unsigned int flags,
    taa_window* w_out);

taa_SDK_LINKAGE void taa_window_destroy(
    taa_window_display disp,
    taa_window win);

taa_SDK_LINKAGE void taa_window_get_size(
    taa_window_display disp,
    taa_window win,
    unsigned int* w_out,
    unsigned int* h_out);

taa_SDK_LINKAGE taa_window_display taa_window_open_display();

taa_SDK_LINKAGE void taa_window_show(
    taa_window_display disp,
    taa_window win,
    int visible);

/**
 * @return the number of events recorded
 */
taa_SDK_LINKAGE unsigned int taa_window_update(
    taa_window_display disp,
    taa_window win,
    taa_window_event* events_out,
    unsigned int maxevents);

#endif // taa_WINDOW_H_
