/**
 * @brief     mouse input implementation for win32
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
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient((HWND) win, &pt);
    mouse_out->cursorx = pt.x;
    mouse_out->cursory = pt.y;
    mouse_out->button1 = (GetKeyState(VK_LBUTTON) & 0x80) != 0;
    mouse_out->button2 = (GetKeyState(VK_MBUTTON) & 0x80) != 0;
    mouse_out->button3 = (GetKeyState(VK_RBUTTON) & 0x80) != 0;
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
