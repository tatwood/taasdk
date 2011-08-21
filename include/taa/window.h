/**
 * @brief     target agnostic window management header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_WINDOW_H_
#define TAA_WINDOW_H_

#include "keyboard.h"
#include "mouse.h"
#include "system.h"

//****************************************************************************
// typedefs

typedef enum taa_window_eventtype_e taa_window_eventtype;

typedef struct taa_window_mouseevent_s taa_window_mouseevent;
typedef struct taa_window_keyevent_s taa_window_keyevent;
typedef union taa_window_event_u taa_window_event;

typedef struct taa_window_display_s taa_window_display;
typedef struct taa_window_state_s taa_window_state;
typedef struct taa_window_visualinfo_s taa_window_visualinfo;
typedef struct taa_window_s taa_window;

//****************************************************************************
// enums

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
// structs

struct taa_window_mouseevent_s
{
    taa_window_eventtype type;
    taa_mouse_state state;
};

struct taa_window_keyevent_s
{
    taa_window_eventtype type;
    uint8_t keycode;
    char ascii;
};

union taa_window_event_u
{
    taa_window_eventtype type;
    taa_window_keyevent key;
    taa_window_mouseevent mouse;
};

struct taa_window_state_s
{
    int32_t width;
    int32_t height;
    int32_t numevents;
    taa_keyboard_state kbstate;
    taa_mouse_state mousestate;
    taa_window_event events[32];
};

//****************************************************************************
// functions

taa_EXTERN_C void taa_window_choosevisualinfo(
    taa_window_display* display,
    taa_window_visualinfo* viout);

taa_EXTERN_C void taa_window_closedisplay(
    taa_window_display* disp);

taa_EXTERN_C void taa_window_create(
    taa_window_display* disp,
    taa_window_visualinfo* vi,
    const char* title,
    int32_t width,
    int32_t height,
    taa_window* wout);

taa_EXTERN_C void taa_window_destroy(
    taa_window* w);

taa_EXTERN_C void taa_window_opendisplay(
    taa_window_display* dispout);

taa_EXTERN_C void taa_window_show(
    taa_window* w,
    int32_t visible);

taa_EXTERN_C void taa_window_update(
    taa_window* w,
    taa_window_state* stateout);

//****************************************************************************
// platform includes

#ifdef WIN32
#include "window_win32.h"
#else
#include "window_x11.h"
#endif

#endif // TAA_WINDOW_H_
