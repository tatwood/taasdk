/**
 * @brief     mouse input implementation for X11
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by mouse.c
#ifdef taa_MOUSE_C_
#include <taa/mouse.h>

//****************************************************************************
void taa_mouse_query(
    taa_window_display disp,
    taa_window win,
    taa_mouse_state* mouse_out)
{
    Window root;
    Window child;
    int rootx;
    int rooty;
    unsigned state;
    XQueryPointer(
        (Display*) disp,
        (Window) win,
        &root,
        &child,
        &rootx,
        &rooty,
        &mouse_out->cursorx,
        &mouse_out->cursory,
        &state);
    mouse_out->button1 = ((state & Button1Mask) != 0);
    mouse_out->button2 = ((state & Button2Mask) != 0);
    mouse_out->button3 = ((state & Button3Mask) != 0);
}

//****************************************************************************
void taa_mouse_update(
    const taa_window_event* events,
    uint32_t numevents,
    taa_mouse_state* mouse_out)
{
    const taa_window_event* evtitr = events;
    const taa_window_event* evtend = evtitr + numevents;
    while(evtitr != evtend)
    {
        switch(evtitr->type)
        {
        case taa_WINDOW_EVENT_DEACTIVATE:
            // if focus lost, clear button state
            mouse_out->button1 = 0;
            mouse_out->button2 = 0;
            mouse_out->button3 = 0;
            break;
        case taa_WINDOW_EVENT_MOUSE_BUTTON1_DOWN:
            mouse_out->cursorx = evtitr->mouse.cursorx;
            mouse_out->cursory = evtitr->mouse.cursory;
            mouse_out->button1 = 1;
            mouse_out->button2 = evtitr->mouse.button2;
            mouse_out->button3 = evtitr->mouse.button3;
            break;
        case taa_WINDOW_EVENT_MOUSE_BUTTON1_UP:
            mouse_out->cursorx = evtitr->mouse.cursorx;
            mouse_out->cursory = evtitr->mouse.cursory;
            mouse_out->button1 = 0;
            mouse_out->button2 = evtitr->mouse.button2;
            mouse_out->button3 = evtitr->mouse.button3;
            break;
        case taa_WINDOW_EVENT_MOUSE_BUTTON2_DOWN:
            mouse_out->cursorx = evtitr->mouse.cursorx;
            mouse_out->cursory = evtitr->mouse.cursory;
            mouse_out->button1 = evtitr->mouse.button1;
            mouse_out->button2 = 1;
            mouse_out->button3 = evtitr->mouse.button3;
            break;
        case taa_WINDOW_EVENT_MOUSE_BUTTON2_UP:
            mouse_out->cursorx = evtitr->mouse.cursorx;
            mouse_out->cursory = evtitr->mouse.cursory;
            mouse_out->button1 = evtitr->mouse.button1;
            mouse_out->button2 = 0;
            mouse_out->button3 = evtitr->mouse.button3;
            break;
        case taa_WINDOW_EVENT_MOUSE_BUTTON3_DOWN:
            mouse_out->cursorx = evtitr->mouse.cursorx;
            mouse_out->cursory = evtitr->mouse.cursory;
            mouse_out->button1 = evtitr->mouse.button1;
            mouse_out->button2 = evtitr->mouse.button2;
            mouse_out->button3 = 1;
            break;
        case taa_WINDOW_EVENT_MOUSE_BUTTON3_UP:
            mouse_out->cursorx = evtitr->mouse.cursorx;
            mouse_out->cursory = evtitr->mouse.cursory;
            mouse_out->button1 = evtitr->mouse.button1;
            mouse_out->button2 = evtitr->mouse.button2;
            mouse_out->button3 = 0;
            break;
        case taa_WINDOW_EVENT_MOUSE_MOVE:
            mouse_out->cursorx = evtitr->mouse.cursorx;
            mouse_out->cursory = evtitr->mouse.cursory;
            break;
        default:
            break;
        }
        ++evtitr;
    }
}
#endif // taa_MOUSE_C_
