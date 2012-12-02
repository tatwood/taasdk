/**
 * @brief     target agnostic header for mouse input
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_MOUSE_H_
#define taa_MOUSE_H_

#include "window.h"

typedef struct taa_mouse_state_s taa_mouse_state;

struct taa_mouse_state_s
{
    int32_t cursorx;
    int32_t cursory;
    int8_t button1;
    int8_t button2;
    int8_t button3;
};

//****************************************************************************
// functions

taa_SDK_LINKAGE void taa_mouse_query(
    taa_window_display disp,
    taa_window win,
    taa_mouse_state* mouse_out);

/**
 * updates an existing mouse state based on a set of window events
 */
taa_SDK_LINKAGE void taa_mouse_update(
    const taa_window_event* events,
    uint32_t numevents,
    taa_mouse_state* mouse);

#endif // taa_MOUSE_H_
