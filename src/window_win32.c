/**
 * @brief     window management implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by window.c
#ifdef taa_WINDOW_C_
#include <taa/window.h>
#include <taa/keyboard.h>
#include <assert.h>
#include <stdlib.h>
#include <windowsx.h>

typedef struct taa_window_procdata_s taa_window_procdata;

struct taa_window_procdata_s
{
    taa_window_display display;
    taa_window_event* events;
    taa_window_event* evtitr;
    taa_window_event* evtend;
    int lshift;
    int lctrl;
    int lalt;
};

//****************************************************************************
static LRESULT CALLBACK taa_window_proc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    int retval = -1;
    LONG_PTR wlptr = (LONG_PTR) GetWindowLongPtr(hWnd, GWL_USERDATA);
    taa_window_procdata* data = (taa_window_procdata*) wlptr;
    // no custom message processing unless there's a place to store them
    if(data != NULL)
    {
        // NOTE: always check for event buffer end, because this function
        // may be called recursively by DefWindowProc during dispatch of a
        // single msg. if too many events are received in a single frame, it
        // just drops them.
        taa_window_event* evtitr = data->evtitr;
        taa_window_event* evtend = data->evtend;
        switch(uMsg)
        {
        case WM_ACTIVATE:
            // window activated / deactivated
            if(evtitr < evtend)
            {
                evtitr->type = (HIWORD(wParam)) ?
                    taa_WINDOW_EVENT_DEACTIVATE :
                    taa_WINDOW_EVENT_ACTIVATE;
                ++evtitr;
            }
            retval = 0;
            break;
        case WM_CLOSE:
            // window closed
            if(evtitr < evtend)
            {
                evtitr->type = taa_WINDOW_EVENT_CLOSE;
                ++evtitr;
            }
            retval = 0;
            break;
        case WM_CREATE:
            // window created
            {
            }
            retval = 0;
            break;
        case WM_DESTROY:
            // window destroyed
            PostQuitMessage(0);
            retval = 0;
            break;
        case WM_KEYDOWN:
            // key is down
            {
                WORD ascii;
                BYTE kbstate[256];
                int lshift;
                int lctrl;
                int lalt;
                GetKeyboardState(kbstate);
                lshift = kbstate[VK_LSHIFT  ] & 0x80;
                lctrl  = kbstate[VK_LCONTROL] & 0x80;
                lalt   = kbstate[VK_LMENU   ] & 0x80;
                if(ToAscii((UINT)wParam,(UINT) lParam,kbstate,&ascii,0) != 1)
                {
                    ascii = 0;
                }
                if(evtitr < evtend)
                {
                    int key;
                    switch(wParam)
                    {
                    case VK_SHIFT:
                        key= (lshift!=data->lshift) ? VK_LSHIFT : VK_RSHIFT;
                        break;
                    case VK_CONTROL:
                        key= (lctrl!=data->lctrl) ? VK_LCONTROL : VK_RCONTROL;
                        break;
                    case VK_MENU:
                        key= (lalt!=data->lalt) ? VK_LMENU : VK_RMENU;
                        break;
                    default:
                        key= (int) wParam;
                        break;
                    }
                    key = taa_keyboard_translate(data->display, key);
                    evtitr->key.type = taa_WINDOW_EVENT_KEY_DOWN;
                    evtitr->key.keycode = (uint8_t) key;
                    evtitr->key.ascii = (char) ascii;
                    ++evtitr;
                }
                data->lshift = lshift;
                data->lctrl  = lctrl;
                data->lalt   = lalt;
            }
            retval = 0;
            break;
        case WM_KEYUP:
            // key is up
            {
                int lshift = (GetKeyState(VK_LSHIFT  ) & 0x8000) >> 8;
                int lctrl  = (GetKeyState(VK_LCONTROL) & 0x8000) >> 8;
                int lalt   = (GetKeyState(VK_LMENU   ) & 0x8000) >> 8;                
                if(evtitr < evtend)
                {
                    int key;
                    switch(wParam)
                    {
                    case VK_SHIFT:
                        key= (lshift!=data->lshift) ? VK_LSHIFT : VK_RSHIFT;
                        break;
                    case VK_CONTROL:
                        key= (lctrl!=data->lctrl) ? VK_LCONTROL : VK_RCONTROL;
                        break;
                    case VK_MENU:
                        key= (lalt!=data->lalt) ? VK_LMENU : VK_RMENU;
                        break;
                    default:
                        key= (int) wParam;
                        break;
                    }
                    key = taa_keyboard_translate(data->display, key);
                    evtitr->key.type = taa_WINDOW_EVENT_KEY_UP;
                    evtitr->key.keycode = (uint8_t) key;
                    evtitr->key.ascii = '\0';
                    ++evtitr;
                }
                data->lshift = lshift;
                data->lctrl  = lctrl;
                data->lalt   = lalt;
            }
            retval = 0;
            break;
        case WM_KILLFOCUS:
            // lost keyboard focus
            ReleaseCapture(); // release the mouse
            retval = 0;
            break;
        case WM_LBUTTONDOWN:
            // left mouse down
            SetCapture(hWnd);
            if(evtitr < evtend)
            {
                evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON1_DOWN;
                evtitr->mouse.cursorx = GET_X_LPARAM(lParam);
                evtitr->mouse.cursory = GET_Y_LPARAM(lParam);
                evtitr->mouse.button1 = (wParam & MK_LBUTTON) != 0;
                evtitr->mouse.button2 = (wParam & MK_MBUTTON) != 0;
                evtitr->mouse.button3 = (wParam & MK_RBUTTON) != 0;
                ++evtitr;
            }
            retval = 0;
            break;
        case WM_LBUTTONUP:
            // left mouse up
            ReleaseCapture();
            if(evtitr < evtend)
            {
                evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON1_UP;
                evtitr->mouse.cursorx = GET_X_LPARAM(lParam);
                evtitr->mouse.cursory = GET_Y_LPARAM(lParam);
                evtitr->mouse.button1 = (wParam & MK_LBUTTON) != 0;
                evtitr->mouse.button2 = (wParam & MK_MBUTTON) != 0;
                evtitr->mouse.button3 = (wParam & MK_RBUTTON) != 0;
                ++evtitr;
            }
            retval = 0;
            break;
        case WM_MBUTTONDOWN:
            // middle mouse down
            SetCapture(hWnd);
            if(evtitr < evtend)
            {
                evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON2_DOWN;
                evtitr->mouse.cursorx = GET_X_LPARAM(lParam);
                evtitr->mouse.cursory = GET_Y_LPARAM(lParam);
                evtitr->mouse.button1 = (wParam & MK_LBUTTON) != 0;
                evtitr->mouse.button2 = (wParam & MK_MBUTTON) != 0;
                evtitr->mouse.button3 = (wParam & MK_RBUTTON) != 0;
                ++evtitr;
            }
            retval = 0;
            break;
        case WM_MBUTTONUP:
            // middle mouse up
            ReleaseCapture();
            if(evtitr < evtend)
            {
                evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON2_UP;
                evtitr->mouse.cursorx = GET_X_LPARAM(lParam);
                evtitr->mouse.cursory = GET_Y_LPARAM(lParam);
                evtitr->mouse.button1 = (wParam & MK_LBUTTON) != 0;
                evtitr->mouse.button2 = (wParam & MK_MBUTTON) != 0;
                evtitr->mouse.button3 = (wParam & MK_RBUTTON) != 0;
                ++evtitr;
            }
            retval = 0;
            break;
        case WM_MOUSEMOVE:
            // mouse moved
            if(evtitr < evtend)
            {
                evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_MOVE;
                evtitr->mouse.cursorx = GET_X_LPARAM(lParam);
                evtitr->mouse.cursory = GET_Y_LPARAM(lParam);
                evtitr->mouse.button1 = (wParam & MK_LBUTTON) != 0;
                evtitr->mouse.button2 = (wParam & MK_MBUTTON) != 0;
                evtitr->mouse.button3 = (wParam & MK_RBUTTON) != 0;
                ++evtitr;
            }
            retval = 0;
            break;
        case WM_QUIT:
            // quit request
            if(evtitr < evtend)
            {
                evtitr->type = taa_WINDOW_EVENT_CLOSE;
                ++evtitr;
            }
            retval = 0;
            break;
        case WM_RBUTTONDOWN:
            // right mouse down
            SetCapture(hWnd);
            if(evtitr < evtend)
            {
                evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON3_DOWN;
                evtitr->mouse.cursorx = GET_X_LPARAM(lParam);
                evtitr->mouse.cursory = GET_Y_LPARAM(lParam);
                evtitr->mouse.button1 = (wParam & MK_LBUTTON) != 0;
                evtitr->mouse.button2 = (wParam & MK_MBUTTON) != 0;
                evtitr->mouse.button3 = (wParam & MK_RBUTTON) != 0;
                ++evtitr;
            }
            retval = 0;
            break;
        case WM_RBUTTONUP:
            // right mouse up
            ReleaseCapture();
            if(evtitr < evtend)
            {
                evtitr->mouse.type = taa_WINDOW_EVENT_MOUSE_BUTTON3_UP;
                evtitr->mouse.cursorx = GET_X_LPARAM(lParam);
                evtitr->mouse.cursory = GET_Y_LPARAM(lParam);
                evtitr->mouse.button1 = (wParam & MK_LBUTTON) != 0;
                evtitr->mouse.button2 = (wParam & MK_MBUTTON) != 0;
                evtitr->mouse.button3 = (wParam & MK_RBUTTON) != 0;
                ++evtitr;
            }
            retval = 0;
            break;
        case WM_SIZE:
            // window resized
            {
                // in order to ensure that the most accurate window size is
                // reported to the application, only one resize event is
                // reported per frame. otherwise, a situation could develop
                // where the most recent of multiple resize events could be
                // dropped to prevent buffer overflow.
                taa_window_event* sizeevt = data->events;
                while(sizeevt < evtitr)
                {
                    if(sizeevt->type == taa_WINDOW_EVENT_SIZE)
                    {
                        break;
                    }
                    ++sizeevt;
                }
                if(sizeevt < evtend)
                {
                    sizeevt->size.type = taa_WINDOW_EVENT_SIZE;
                    sizeevt->size.width = LOWORD(lParam);
                    sizeevt->size.height = HIWORD(lParam);
                    if(sizeevt == evtitr)
                    {
                        ++evtitr;
                    }
                }
            }
            retval = 0;
            break;
        case WM_SYSCOMMAND:
            // screensaver
            if(wParam == SC_SCREENSAVE || wParam == SC_MONITORPOWER)
            {
                // prevent screen saver & monitor power save
                retval = 0;
            }
            break;
        }
        // record new position in event array
        data->evtitr = evtitr;
    }
    // Pass all unhandled messages to DefWindowProc
    if(retval != 0)
    {
        retval = DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return retval;
}

//****************************************************************************
void taa_window_close_display(
    taa_window_display disp)
{
    // nothing to do
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
    HINSTANCE hinstance;
    WNDCLASS wc;
    ATOM classid;
    HWND hwnd;
    RECT window_rect;
    DWORD dwExStyle;
    DWORD dwStyle;
    // create the window class
    hinstance = GetModuleHandle(NULL);
    wc.style            = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc      = taa_window_proc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hinstance;
    wc.hIcon            = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL; 
    wc.lpszClassName    = title;
    classid = RegisterClass(&wc);
    err = (classid!=0) ? 0 : -1;
    if(err == 0)
    {
        if(flags & taa_WINDOW_FULLSCREEN)
        {
            dwExStyle=WS_EX_APPWINDOW;
            dwStyle=WS_POPUP;
            window_rect.left = 0;
            window_rect.right = GetSystemMetrics(SM_CXSCREEN);
            window_rect.top = 0;
            window_rect.bottom = GetSystemMetrics(SM_CYSCREEN);
        }
        else
        {
            dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
            dwStyle=WS_OVERLAPPEDWINDOW; 
            window_rect.left = 0;
            window_rect.right = width;
            window_rect.top = 0;
            window_rect.bottom = height;
            AdjustWindowRectEx(&window_rect, dwStyle, FALSE, dwExStyle);
        }

        // create the window.
        hwnd = CreateWindowEx(
            dwExStyle,
            MAKEINTATOM(classid),
            title,
            dwStyle|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
            0,
            0,
            window_rect.right-window_rect.left,
            window_rect.bottom-window_rect.top,
            NULL,
            NULL,
            hinstance,
            NULL);
        err = (hwnd!=NULL) ? 0 : -1;
    }
    if(err == 0)
    {
        SetForegroundWindow(hwnd);
        SetFocus(hwnd);
        *w_out = (taa_window) hwnd;
    }
    return err;
}

//****************************************************************************
void taa_window_destroy(
    taa_window_display disp,
    taa_window win)
{
    // Destroy the window
    WORD classid = GetClassWord((HWND) win, GCW_ATOM);
    int r;
    r = DestroyWindow((HWND) win);
    assert(r);
    // Unregister the class
    r = UnregisterClass(MAKEINTATOM(classid), GetModuleHandle(NULL));
    assert(r);
}

//****************************************************************************
void taa_window_get_size(
    taa_window_display disp,
    taa_window win,
    unsigned int* w_out,
    unsigned int* h_out)
{
    RECT rect;
    GetClientRect((HWND) win, &rect);
    *w_out = rect.right;
    *h_out = rect.bottom;
}

//****************************************************************************
taa_window_display taa_window_open_display()
{
    return taa_window_open_display;
}

//****************************************************************************
void taa_window_show(
    taa_window_display disp,
    taa_window win,
    int visible)
{
    ShowWindow((HWND) win, (visible) ? SW_SHOW : SW_HIDE);
}

//****************************************************************************
unsigned int taa_window_update(
    taa_window_display disp,
    taa_window win,
    taa_window_event* events_out,
    unsigned int maxevents)
{
    taa_window_procdata data;
    taa_window_event** evtref;
    MSG msg;
    LONG_PTR wlptr;

    // attach the structure to the window
    data.display = disp;
    data.events = events_out;
    data.evtitr = events_out;
    data.evtend = data.evtitr + maxevents;
    data.lshift = (GetKeyState(VK_LSHIFT  ) & 0x8000) >> 8;
    data.lctrl  = (GetKeyState(VK_LCONTROL) & 0x8000) >> 8;
    data.lalt   = (GetKeyState(VK_LMENU   ) & 0x8000) >> 8;
    wlptr = (LONG_PTR) &data;
#if _WIN64
    SetWindowLongPtr((HWND) win,GWL_USERDATA, wlptr);
#else
    SetWindowLong((HWND) win, GWL_USERDATA, (LONG) wlptr);
#endif

    evtref = &data.evtitr;
    while(*evtref < data.evtend)
    {
        if(!PeekMessage(&msg, (HWND) win, 0, 0, PM_REMOVE))
        {
            break;
        }

        if (msg.message == WM_QUIT)
        {
            data.evtitr->type = taa_WINDOW_EVENT_CLOSE;
            ++data.evtitr;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    assert(data.evtitr <= data.evtend);

#if _WIN64
    SetWindowLongPtr((HWND) win,GWL_USERDATA, NULL);
#else
    SetWindowLong((HWND) win, GWL_USERDATA, (LONG) NULL);
#endif
    return (unsigned int) (uintptr_t) (data.evtitr - events_out);
}

#endif // taa_WINDOW_C_

