/**
 * @brief     window management header for X11
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by window.c
#ifdef TAA_WINDOW_C_

#include <taa/error.h>
#include <X11/Xutil.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    taa_WINDOW_XKMAP_SIZE = 256
};

static uint8_t taa_s_window_keycodemap[taa_WINDOW_XKMAP_SIZE];

//****************************************************************************
static void taa_window_mapkey(
    Display* d,
    KeySym ks,
    uint8_t key)
{
    uint8_t xcode = XKeysymToKeycode(d, ks);
    assert((xcode & 0xff) ==  xcode);
    assert(taa_s_window_keycodemap[xcode] == taa_KEY_UNKNOWN);
    taa_s_window_keycodemap[xcode] = key;
}

//****************************************************************************
static int32_t taa_window_translatekey(
    Display* d,
    int32_t xk)
{
    static uint8_t* map = NULL;
    if(map == NULL)
    {
        int32_t i;
        for(i = 0; i < taa_WINDOW_XKMAP_SIZE; ++i)
        {
            taa_s_window_keycodemap[i] = taa_KEY_UNKNOWN;
        }
        taa_window_mapkey(d,XK_BackSpace   ,taa_KEY_BACKSPACE);
        taa_window_mapkey(d,XK_Tab         ,taa_KEY_TAB);
        taa_window_mapkey(d,XK_Return      ,taa_KEY_ENTER);
        taa_window_mapkey(d,XK_Shift_L     ,taa_KEY_SHIFT);
        taa_window_mapkey(d,XK_Shift_R     ,taa_KEY_SHIFT);
        taa_window_mapkey(d,XK_Control_L   ,taa_KEY_CTRL);
        taa_window_mapkey(d,XK_Control_R   ,taa_KEY_CTRL);
        taa_window_mapkey(d,XK_Alt_L       ,taa_KEY_ALT);
        taa_window_mapkey(d,XK_Alt_R       ,taa_KEY_ALT);
        taa_window_mapkey(d,XK_Pause       ,taa_KEY_PAUSE);
        taa_window_mapkey(d,XK_Caps_Lock   ,taa_KEY_CAPSLOCK);
        taa_window_mapkey(d,XK_Escape      ,taa_KEY_ESCAPE);
        taa_window_mapkey(d,XK_space       ,taa_KEY_SPACE);
        taa_window_mapkey(d,XK_Prior       ,taa_KEY_PAGE_UP);
        taa_window_mapkey(d,XK_Next        ,taa_KEY_PAGE_DOWN);
        taa_window_mapkey(d,XK_End         ,taa_KEY_END);
        taa_window_mapkey(d,XK_Home        ,taa_KEY_HOME);
        taa_window_mapkey(d,XK_Left        ,taa_KEY_LEFT);
        taa_window_mapkey(d,XK_Up          ,taa_KEY_UP);
        taa_window_mapkey(d,XK_Right       ,taa_KEY_RIGHT);
        taa_window_mapkey(d,XK_Down        ,taa_KEY_DOWN);
        taa_window_mapkey(d,XK_Print       ,taa_KEY_PRINTSCREEN);
        taa_window_mapkey(d,XK_Insert      ,taa_KEY_INSERT);
        taa_window_mapkey(d,XK_Delete      ,taa_KEY_DELETE);
        taa_window_mapkey(d,'0'            ,taa_KEY_0);
        taa_window_mapkey(d,'1'            ,taa_KEY_1);
        taa_window_mapkey(d,'2'            ,taa_KEY_2);
        taa_window_mapkey(d,'3'            ,taa_KEY_3);
        taa_window_mapkey(d,'4'            ,taa_KEY_4);
        taa_window_mapkey(d,'5'            ,taa_KEY_5);
        taa_window_mapkey(d,'6'            ,taa_KEY_6);
        taa_window_mapkey(d,'7'            ,taa_KEY_7);
        taa_window_mapkey(d,'8'            ,taa_KEY_8);
        taa_window_mapkey(d,'9'            ,taa_KEY_9);
        taa_window_mapkey(d,'a'            ,taa_KEY_A);
        taa_window_mapkey(d,'b'            ,taa_KEY_B);
        taa_window_mapkey(d,'c'            ,taa_KEY_C);
        taa_window_mapkey(d,'d'            ,taa_KEY_D);
        taa_window_mapkey(d,'e'            ,taa_KEY_E);
        taa_window_mapkey(d,'f'            ,taa_KEY_F);
        taa_window_mapkey(d,'g'            ,taa_KEY_G);
        taa_window_mapkey(d,'h'            ,taa_KEY_H);
        taa_window_mapkey(d,'i'            ,taa_KEY_I);
        taa_window_mapkey(d,'j'            ,taa_KEY_J);
        taa_window_mapkey(d,'k'            ,taa_KEY_K);
        taa_window_mapkey(d,'l'            ,taa_KEY_L);
        taa_window_mapkey(d,'m'            ,taa_KEY_M);
        taa_window_mapkey(d,'n'            ,taa_KEY_N);
        taa_window_mapkey(d,'o'            ,taa_KEY_O);
        taa_window_mapkey(d,'p'            ,taa_KEY_P);
        taa_window_mapkey(d,'q'            ,taa_KEY_Q);
        taa_window_mapkey(d,'r'            ,taa_KEY_R);
        taa_window_mapkey(d,'s'            ,taa_KEY_S);
        taa_window_mapkey(d,'t'            ,taa_KEY_T);
        taa_window_mapkey(d,'u'            ,taa_KEY_U);
        taa_window_mapkey(d,'v'            ,taa_KEY_V);
        taa_window_mapkey(d,'w'            ,taa_KEY_W);
        taa_window_mapkey(d,'x'            ,taa_KEY_X);
        taa_window_mapkey(d,'y'            ,taa_KEY_Y);
        taa_window_mapkey(d,'z'            ,taa_KEY_Z);
        taa_window_mapkey(d,XK_Super_L     ,taa_KEY_LWIN);
        taa_window_mapkey(d,XK_Super_R     ,taa_KEY_RWIN);
        taa_window_mapkey(d,XK_Menu        ,taa_KEY_APPLICATION);
        taa_window_mapkey(d,XK_KP_0        ,taa_KEY_NUMPAD_0);
        taa_window_mapkey(d,XK_KP_1        ,taa_KEY_NUMPAD_1);
        taa_window_mapkey(d,XK_KP_2        ,taa_KEY_NUMPAD_2);
        taa_window_mapkey(d,XK_KP_3        ,taa_KEY_NUMPAD_3);
        taa_window_mapkey(d,XK_KP_4        ,taa_KEY_NUMPAD_4);
        taa_window_mapkey(d,XK_KP_5        ,taa_KEY_NUMPAD_5);
        taa_window_mapkey(d,XK_KP_6        ,taa_KEY_NUMPAD_6);
        taa_window_mapkey(d,XK_KP_7        ,taa_KEY_NUMPAD_7);
        taa_window_mapkey(d,XK_KP_8        ,taa_KEY_NUMPAD_8);
        taa_window_mapkey(d,XK_KP_9        ,taa_KEY_NUMPAD_9);
        taa_window_mapkey(d,XK_KP_Multiply ,taa_KEY_NUMPAD_MULTIPLY);
        taa_window_mapkey(d,XK_KP_Add      ,taa_KEY_NUMPAD_ADD);
        taa_window_mapkey(d,XK_KP_Separator,taa_KEY_NUMPAD_SEPARATOR);
        taa_window_mapkey(d,XK_KP_Subtract ,taa_KEY_NUMPAD_SUBTRACT);
        taa_window_mapkey(d,XK_KP_Decimal  ,taa_KEY_NUMPAD_DECIMAL);
        taa_window_mapkey(d,XK_KP_Divide   ,taa_KEY_NUMPAD_DIVIDE);
        taa_window_mapkey(d,XK_F1          ,taa_KEY_F1);
        taa_window_mapkey(d,XK_F2          ,taa_KEY_F2);
        taa_window_mapkey(d,XK_F3          ,taa_KEY_F3);
        taa_window_mapkey(d,XK_F4          ,taa_KEY_F4);
        taa_window_mapkey(d,XK_F5          ,taa_KEY_F5);
        taa_window_mapkey(d,XK_F6          ,taa_KEY_F6);
        taa_window_mapkey(d,XK_F7          ,taa_KEY_F7);
        taa_window_mapkey(d,XK_F8          ,taa_KEY_F8);
        taa_window_mapkey(d,XK_F9          ,taa_KEY_F9);
        taa_window_mapkey(d,XK_F10         ,taa_KEY_F10);
        taa_window_mapkey(d,XK_F11         ,taa_KEY_F11);
        taa_window_mapkey(d,XK_F12         ,taa_KEY_F12);
        taa_window_mapkey(d,XK_Num_Lock    ,taa_KEY_NUMLOCK);
        taa_window_mapkey(d,XK_Scroll_Lock ,taa_KEY_SCROLL);
        taa_window_mapkey(d,XK_semicolon   ,taa_KEY_SEMICOLON);
        taa_window_mapkey(d,XK_equal       ,taa_KEY_EQUAL);
        taa_window_mapkey(d,XK_comma       ,taa_KEY_COMMA);
        taa_window_mapkey(d,XK_minus       ,taa_KEY_MINUS);
        taa_window_mapkey(d,XK_period      ,taa_KEY_PERIOD);
        taa_window_mapkey(d,XK_slash       ,taa_KEY_SLASH);
        taa_window_mapkey(d,XK_grave       ,taa_KEY_BACKQUOTE);
        taa_window_mapkey(d,XK_bracketleft ,taa_KEY_LEFTBRACKET);
        taa_window_mapkey(d,XK_backslash   ,taa_KEY_BACKSLASH);
        taa_window_mapkey(d,XK_bracketright,taa_KEY_RIGHTBRACKET);
        taa_window_mapkey(d,XK_apostrophe  ,taa_KEY_QUOTE);
        map = taa_s_window_keycodemap;
    }
    return (int32_t) map[xk & (taa_WINDOW_XKMAP_SIZE - 1)];
}

//****************************************************************************
void taa_window_closedisplay(
    taa_window_display* disp)
{
    XCloseDisplay(disp->x11.display);
}

//****************************************************************************
void taa_window_create(
    taa_window_display* disp,
    taa_window_visualinfo* vi,
    const char* title,
    int32_t width,
    int32_t height,
    taa_window* wout)
{
    Display* display = disp->x11.display;
    int32_t screen = disp->x11.screen;
    Visual* visual = vi->x11.visual;
    Window root;
    Colormap colormap;
    XSetWindowAttributes swa;
    Window xwin;
    Atom wmdelete;
    taa_window_state* state;

    state = (taa_window_state*) calloc(1, sizeof(*state));
    wout->x11.state = state;

    // create a colormap
    root = XRootWindow(display, screen);
    colormap = XCreateColormap(display, root, visual, AllocNone);

    // create a window
    swa.background_pixel = 0;
    swa.border_pixel = 0;
    swa.colormap = colormap;
    swa.event_mask =
        ExposureMask |
        FocusChangeMask |
        KeyPressMask |
        KeyReleaseMask |
        ButtonPressMask |
        ButtonReleaseMask |
        PointerMotionMask |
        StructureNotifyMask;
    xwin = XCreateWindow(
        display,
        root,
        20,
        20,
        width,
        height,
        0,
        XDefaultDepth(display, screen),
        InputOutput,
        visual,
        CWBackPixel|CWBorderPixel|CWColormap|CWEventMask,
        &swa);
    // set the title
    XStoreName(display, xwin, title);
    // listen to close window requests
    wmdelete = XInternAtom(display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(display, xwin, &wmdelete, 1);

    wout->x11.display = display;
    wout->x11.colormap = colormap;
    wout->x11.window = xwin;
    wout->x11.wmdelete = wmdelete;
    wout->x11.state->width = width;
    wout->x11.state->height = height;
    wout->x11.state->numevents = 0;
}

//****************************************************************************
void taa_window_destroy(
    taa_window* w)
{
    XDestroyWindow(w->x11.display, w->x11.window);
    XFreeColormap(w->x11.display, w->x11.colormap);
    free(w->x11.state);
}

//****************************************************************************
void taa_window_opendisplay(
    taa_window_display* dispout)
{
    Display* display = XOpenDisplay(0);
    taa_CHECK_ERROR(display != NULL, "cannot connect to X server");
    dispout->x11.display = display;
    dispout->x11.screen = XDefaultScreen(display);
}

//****************************************************************************
void taa_window_show(
    taa_window* w,
    int32_t visible)
{
    if(visible)
    {
        // make the window visible
        XMapWindow(w->x11.display, w->x11.window);
    }
    else
    {
        XUnmapWindow(w->x11.display, w->x11.window);
    }
}

//****************************************************************************
void taa_window_update(
    taa_window* w,
    taa_window_state* stateout)
{
    int32_t numevents = 0;
    char ascii;
    taa_window_state* state = w->x11.state;
    Display* display = w->x11.display;
    XEvent evt;

    while(numevents < (sizeof(state->events)/sizeof(*state->events)))
    {
        if(!XEventsQueued(display, QueuedAfterFlush))
        {
            break;
        }
        XNextEvent(display, &evt);
        switch(evt.type)
        {
        case ButtonPress:
            // mouse button is down
            {
                taa_window_mouseevent* mouseevt;
                // capture mouse events until button is released
                XGrabPointer(
                    display,
                    w->x11.window,
                    False,
                    ButtonPressMask|ButtonReleaseMask|PointerMotionMask,
                    GrabModeAsync,
                    GrabModeAsync,
                    None,
                    None,
                    CurrentTime);
                mouseevt = &state->events[numevents++].mouse;
                switch(evt.xbutton.button)
                {
                case Button1:
                    state->mousestate.button1 = 1; // true
                    mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON1_DOWN;
                    break;
                case Button2:
                    state->mousestate.button2 = 1; // true
                    mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON2_DOWN;
                    break;
                default:
                    state->mousestate.button3 = 1; // true
                    mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON3_DOWN;
                    break;
                }
                state->mousestate.cursorx = evt.xbutton.x;
                state->mousestate.cursory = evt.xbutton.y;
                mouseevt->state = state->mousestate;
            }
            break;
        case ButtonRelease:
            // mouse button is up
            {
                taa_window_mouseevent* mouseevt;
                // release hold on mouse events
                XUngrabPointer(display, CurrentTime);
                mouseevt = &state->events[numevents++].mouse;
                switch(evt.xbutton.button)
                {
                case Button1:
                    state->mousestate.button1 = 0; // false
                    mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON1_UP;
                    break;
                case Button2:
                    state->mousestate.button2 = 0; // false
                    mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON2_UP;
                    break;
                default:
                    state->mousestate.button3 = 0; // false
                    mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON3_UP;
                    break;
                }
                state->mousestate.cursorx = evt.xbutton.x;
                state->mousestate.cursory = evt.xbutton.y;
                mouseevt->state = state->mousestate;
            }
            break;
        case ClientMessage:
            // possible close window request
            if(evt.xclient.data.l[0] == ((long) w->x11.wmdelete))
            {
                taa_window_event* winevt;
                winevt = &state->events[numevents++];
                winevt->type = taa_WINDOW_EVENT_CLOSE;
            }
            break;
        case ConfigureNotify:
            // possible window resize
            if (evt.xconfigure.width != state->width ||
                evt.xconfigure.height != state->height)
            {
                taa_window_event* winevt;
                state->width = evt.xconfigure.width;
                state->height = evt.xconfigure.height;
                winevt = &state->events[numevents++];
                winevt->type = taa_WINDOW_EVENT_SIZE;
            }
            break;
        case FocusOut:
            // lost keyboard focus
            {
                // release hold on mouse events
                XUngrabPointer(display, CurrentTime);
                memset(
                    &state->kbstate,
                    0,
                    sizeof(state->kbstate));
                state->mousestate.button1 = 0; // false
                state->mousestate.button2 = 0; // false
                state->mousestate.button3 = 0; // false
            }
            break;
        case KeyPress:
            // key is down
            {
                taa_window_keyevent* keyevt;
                int32_t key;
                ascii = '\0';
                XLookupString(&evt.xkey, &ascii, sizeof(ascii), NULL, NULL);
                key = taa_window_translatekey(display, evt.xkey.keycode);
                if(key != taa_KEY_UNKNOWN)
                {
                    state->kbstate[key] = 1; // true
                }

                keyevt = &state->events[numevents++].key;
                keyevt->type = taa_WINDOW_EVENT_KEY_DOWN;
                keyevt->keycode = key;
                keyevt->ascii = ascii;
            }
            break;
        case KeyRelease:
            // key is up
            {
                // Holding the key down causes a series of KeyRelease,
                // KeyPress pairs. Do not process the KeyRelease unless
                // the key is actually up.
                XEvent next;
                next.type = KeyRelease; // in case nothing is queued
                if(XEventsQueued(display, QueuedAfterReading) > 0)
                {
                    XPeekEvent(display, &next);
                }
                if ((next.type != KeyPress) ||
                    (evt.xkey.time != next.xkey.time) ||
                    (evt.xkey.keycode != next.xkey.keycode))
                {
                    taa_window_keyevent* keyevt;
                    int32_t key;
                    key = taa_window_translatekey(display, evt.xkey.keycode);
                    if(key != taa_KEY_UNKNOWN)
                    {
                        state->kbstate[key] = 0; // false
                    }
                    keyevt = &state->events[numevents++].key;
                    keyevt->type = taa_WINDOW_EVENT_KEY_UP;
                    keyevt->keycode = key;
                    keyevt->ascii = '\0';
                }
            }
            break;
        case MapNotify:
            // window is unhidden / restored
            {
                taa_window_event* winevt;
                winevt = &state->events[numevents++];
                winevt->type = taa_WINDOW_EVENT_ACTIVATE;
            }
            break;
        case MotionNotify:
            // mouse cursor moved
            {
                taa_window_mouseevent* mouseevt;
                state->mousestate.cursorx = evt.xmotion.x;
                state->mousestate.cursory = evt.xmotion.y;
                mouseevt = &state->events[numevents++].mouse;
                mouseevt->type = taa_WINDOW_EVENT_MOUSE_MOVE;
                mouseevt->state = state->mousestate;
            }
            break;
        case UnmapNotify:
            // window is hidden / minimized
            {
                taa_window_event* winevt;
                winevt = &state->events[numevents++];
                winevt->type = taa_WINDOW_EVENT_DEACTIVATE;
            }
            break;
        }
    }
    state->numevents = numevents;

    if(stateout != NULL)
    {
        *stateout = *state;
    }
}

#endif // TAA_WINDOW_C_
