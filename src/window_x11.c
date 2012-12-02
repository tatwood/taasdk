/**
 * @brief     window management header for X11
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by window.c
#ifdef taa_WINDOW_C_
#include <taa/window.h>
#include <taa/keyboard.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//****************************************************************************
void taa_window_close_display(
    taa_window_display disp)
{
    XCloseDisplay((Display*) disp);
}

//****************************************************************************
int taa_window_create(
    taa_window_display disp,
    const char* title,
    unsigned int width,
    unsigned int height,
    unsigned int flags,
    taa_window* w_out)
{
    int err = 0;
    Display* display = (Display*) disp;
    int screen = XDefaultScreen(display);
    Window root;
    XSetWindowAttributes swa;
    Window xwin;
    Atom wmdelete;
    root = XRootWindow(display, screen);
    //swa.colormap = colormap;
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
        CopyFromParent,
        CWEventMask,
        &swa);
    // set the title
    XStoreName(display, xwin, title);
    // listen to close window requests
    wmdelete = XInternAtom(display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(display, xwin, &wmdelete, 1);
    // set fullscreen
    if((flags & taa_WINDOW_FULLSCREEN) != 0)
    {
        Atom atoms[3];
        atoms[0] = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", True);
        atoms[1] = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", True);
        atoms[2] = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", True);
        XChangeProperty(
            disp,
            xwin,
            XInternAtom(display, "_NET_WM_STATE", True),
            XA_ATOM,
            32,
            PropModeReplace, 
            (unsigned char *)atoms,
            3);
    }
    // set out param
    *w_out = xwin;
    return err;
}

//****************************************************************************
void taa_window_destroy(
    taa_window_display disp,
    taa_window win)
{
    XWindowAttributes attr;
    XGetWindowAttributes((Display*) disp, (Window) win, &attr);
    XDestroyWindow((Display*) disp, (Window) win);
    XFreeColormap((Display*) disp, attr.colormap);
}

//****************************************************************************
void taa_window_get_size(
    taa_window_display disp,
    taa_window win,
    unsigned int* w_out,
    unsigned int* h_out)
{
    Window root;
    int x;
    int y;
    unsigned b;
    unsigned d;
    XGetGeometry(disp, win, &root, &x, &y, w_out, h_out, &b, &d);
}

//****************************************************************************
taa_window_display taa_window_open_display()
{
    return XOpenDisplay(0);
}

//****************************************************************************
void taa_window_show(
    taa_window_display disp,
    taa_window win,
    int visible)
{
    if(visible)
    {
        // make the window visible
        XMapWindow((Display*) disp, (Window) win);
    }
    else
    {
        XUnmapWindow((Display*) disp, (Window) win);
    }
}

//****************************************************************************
unsigned int taa_window_update(
    taa_window_display disp,
    taa_window win,
    taa_window_event* events_out,
    unsigned int maxevents)
{
    taa_window_event* evtitr = events_out;
    taa_window_event* evtend = evtitr + maxevents;
    Display* display = (Display*) disp;
    XEvent evt;
    int w;
    int h;
    char ascii;
    // initialize these to zero. if any configure events come in, it will
    // assume the first one is a size event, and will then be able to
    // accurately detect size events after that. at most one redundant
    // size event may be sent per frame.
    w = 0;
    h = 0;
    while(evtitr < evtend)
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
                // capture mouse events until button is released
                XGrabPointer(
                    display,
                    (Window) win,
                    False,
                    ButtonPressMask|ButtonReleaseMask|PointerMotionMask,
                    GrabModeAsync,
                    GrabModeAsync,
                    None,
                    None,
                    CurrentTime);
                switch(evt.xbutton.button)
                {
                case Button1:
                    evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON1_DOWN;
                    break;
                case Button2:
                    evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON2_DOWN;
                    break;
                default:
                    evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON3_DOWN;
                    break;
                }
                evtitr->mouse.cursorx = evt.xbutton.x;
                evtitr->mouse.cursory = evt.xbutton.y;
                evtitr->mouse.button1 = (evt.xbutton.state&Button1Mask) != 0;
                evtitr->mouse.button2 = (evt.xbutton.state&Button2Mask) != 0;
                evtitr->mouse.button3 = (evt.xbutton.state&Button3Mask) != 0;
                ++evtitr;
            }
            break;
        case ButtonRelease:
            // mouse button is up
            {
                // release hold on mouse events
                XUngrabPointer(display, CurrentTime);
                switch(evt.xbutton.button)
                {
                case Button1:
                    evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON1_UP;
                    break;
                case Button2:
                    evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON2_UP;
                    break;
                default:
                   evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON3_UP;
                    break;
                }
                evtitr->mouse.cursorx = evt.xbutton.x;
                evtitr->mouse.cursory = evt.xbutton.y;
                evtitr->mouse.button1 = (evt.xbutton.state&Button1Mask) != 0;
                evtitr->mouse.button2 = (evt.xbutton.state&Button2Mask) != 0;
                evtitr->mouse.button3 = (evt.xbutton.state&Button3Mask) != 0;
                ++evtitr;
            }
            break;
        case ClientMessage:
            // possible close window request
            {
                long wmdel;
                wmdel = (long) XInternAtom(display, "WM_DELETE_WINDOW", True);
                if(evt.xclient.data.l[0] == wmdel)
                {
                    evtitr->type = taa_WINDOW_EVENT_CLOSE;
                    ++evtitr;
                }
            }
            break;
        case ConfigureNotify:
            // possible window resize
            if (evt.xconfigure.width != w || evt.xconfigure.height != h)
            {
                w = evt.xconfigure.width;
                h = evt.xconfigure.height;
                evtitr->size.type = taa_WINDOW_EVENT_SIZE;
                evtitr->size.width = w;
                evtitr->size.height = h;
                ++evtitr;
            }
            break;
        case FocusOut:
            // lost keyboard focus
            // release hold on mouse events
            XUngrabPointer(display, CurrentTime);
            break;
        case KeyPress:
            // key is down
            {
                int key;
                ascii = '\0';
                XLookupString(&evt.xkey, &ascii, sizeof(ascii), NULL, NULL);
                key = taa_keyboard_translate(disp, evt.xkey.keycode);
                evtitr->key.type = taa_WINDOW_EVENT_KEY_DOWN;
                evtitr->key.keycode = key;
                evtitr->key.ascii = ascii;
                ++evtitr;
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
                    int key;
                    key = taa_keyboard_translate(disp,evt.xkey.keycode);
                    evtitr->key.type = taa_WINDOW_EVENT_KEY_UP;
                    evtitr->key.keycode = key;
                    evtitr->key.ascii = '\0';
                    ++evtitr;
                }
            }
            break;
        case MapNotify:
            // window is unhidden / restored
            {
                evtitr->type = taa_WINDOW_EVENT_ACTIVATE;
                ++evtitr;
            }
            break;
        case MotionNotify:
            // mouse cursor moved
            {
                evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_MOVE;
                evtitr->mouse.cursorx = evt.xmotion.x;
                evtitr->mouse.cursory = evt.xmotion.y;
                evtitr->mouse.button1 = (evt.xmotion.state&Button1Mask) != 0;
                evtitr->mouse.button2 = (evt.xmotion.state&Button2Mask) != 0;
                evtitr->mouse.button3 = (evt.xmotion.state&Button3Mask) != 0;
                ++evtitr;
            }
            break;
        case UnmapNotify:
            // window is hidden / minimized
            {
                evtitr->type = taa_WINDOW_EVENT_DEACTIVATE;
                ++evtitr;
            }
            break;
        }
    }
    return (unsigned int) (uintptr_t) (evtitr - events_out);
}

#endif // taa_WINDOW_C_
