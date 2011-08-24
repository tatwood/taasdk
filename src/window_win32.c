/**
 * @brief     window management implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by window.c
#ifdef TAA_WINDOW_C_

#include <taa/error.h>
#include <assert.h>
#include <stdlib.h>

enum
{
    taa_WINDOW_VKMAP_SIZE = 256
};

static uint8_t taa_s_window_keycodemap[taa_WINDOW_VKMAP_SIZE];

//****************************************************************************
static void taa_window_mapkey(
    uint32_t vk,
    uint8_t key)
{
    assert((vk & 0xff) == vk);
    assert(taa_s_window_keycodemap[vk] == taa_KEY_UNKNOWN);
    taa_s_window_keycodemap[vk] = key;
}

//****************************************************************************
static int32_t taa_window_translatekey(
    int32_t vk)
{
    static uint8_t* map = NULL;
    if(map == NULL)
    {
        int32_t i;
        for(i = 0; i < taa_WINDOW_VKMAP_SIZE; ++i)
        {
            taa_s_window_keycodemap[i] = taa_KEY_UNKNOWN;
        }
        taa_window_mapkey(VK_BACK       ,taa_KEY_BACKSPACE);
        taa_window_mapkey(VK_TAB        ,taa_KEY_TAB);
        taa_window_mapkey(VK_RETURN     ,taa_KEY_ENTER);
        taa_window_mapkey(VK_SHIFT      ,taa_KEY_SHIFT);
        taa_window_mapkey(VK_CONTROL    ,taa_KEY_CTRL);
        taa_window_mapkey(VK_MENU       ,taa_KEY_ALT);
        taa_window_mapkey(VK_PAUSE      ,taa_KEY_PAUSE);
        taa_window_mapkey(VK_CAPITAL    ,taa_KEY_CAPSLOCK);
        taa_window_mapkey(VK_ESCAPE     ,taa_KEY_ESCAPE);
        taa_window_mapkey(VK_SPACE      ,taa_KEY_SPACE);
        taa_window_mapkey(VK_PRIOR      ,taa_KEY_PAGE_UP);
        taa_window_mapkey(VK_NEXT       ,taa_KEY_PAGE_DOWN);
        taa_window_mapkey(VK_END        ,taa_KEY_END);
        taa_window_mapkey(VK_HOME       ,taa_KEY_HOME);
        taa_window_mapkey(VK_LEFT       ,taa_KEY_LEFT);
        taa_window_mapkey(VK_UP         ,taa_KEY_UP);
        taa_window_mapkey(VK_RIGHT      ,taa_KEY_RIGHT);
        taa_window_mapkey(VK_DOWN       ,taa_KEY_DOWN);
        taa_window_mapkey(VK_SNAPSHOT   ,taa_KEY_PRINTSCREEN);
        taa_window_mapkey(VK_INSERT     ,taa_KEY_INSERT);
        taa_window_mapkey(VK_DELETE     ,taa_KEY_DELETE);
        taa_window_mapkey('0'           ,taa_KEY_0);
        taa_window_mapkey('1'           ,taa_KEY_1);
        taa_window_mapkey('2'           ,taa_KEY_2);
        taa_window_mapkey('3'           ,taa_KEY_3);
        taa_window_mapkey('4'           ,taa_KEY_4);
        taa_window_mapkey('5'           ,taa_KEY_5);
        taa_window_mapkey('6'           ,taa_KEY_6);
        taa_window_mapkey('7'           ,taa_KEY_7);
        taa_window_mapkey('8'           ,taa_KEY_8);
        taa_window_mapkey('9'           ,taa_KEY_9);
        taa_window_mapkey('A'           ,taa_KEY_A);
        taa_window_mapkey('B'           ,taa_KEY_B);
        taa_window_mapkey('C'           ,taa_KEY_C);
        taa_window_mapkey('D'           ,taa_KEY_D);
        taa_window_mapkey('E'           ,taa_KEY_E);
        taa_window_mapkey('F'           ,taa_KEY_F);
        taa_window_mapkey('G'           ,taa_KEY_G);
        taa_window_mapkey('H'           ,taa_KEY_H);
        taa_window_mapkey('I'           ,taa_KEY_I);
        taa_window_mapkey('J'           ,taa_KEY_J);
        taa_window_mapkey('K'           ,taa_KEY_K);
        taa_window_mapkey('L'           ,taa_KEY_L);
        taa_window_mapkey('M'           ,taa_KEY_M);
        taa_window_mapkey('N'           ,taa_KEY_N);
        taa_window_mapkey('O'           ,taa_KEY_O);
        taa_window_mapkey('P'           ,taa_KEY_P);
        taa_window_mapkey('Q'           ,taa_KEY_Q);
        taa_window_mapkey('R'           ,taa_KEY_R);
        taa_window_mapkey('S'           ,taa_KEY_S);
        taa_window_mapkey('T'           ,taa_KEY_T);
        taa_window_mapkey('U'           ,taa_KEY_U);
        taa_window_mapkey('V'           ,taa_KEY_V);
        taa_window_mapkey('W'           ,taa_KEY_W);
        taa_window_mapkey('X'           ,taa_KEY_X);
        taa_window_mapkey('Y'           ,taa_KEY_Y);
        taa_window_mapkey('Z'           ,taa_KEY_Z);
        taa_window_mapkey(VK_LWIN       ,taa_KEY_LWIN);
        taa_window_mapkey(VK_RWIN       ,taa_KEY_RWIN);
        taa_window_mapkey(VK_APPS       ,taa_KEY_APPLICATION);
        taa_window_mapkey(VK_NUMPAD0    ,taa_KEY_NUMPAD_0);
        taa_window_mapkey(VK_NUMPAD1    ,taa_KEY_NUMPAD_1);
        taa_window_mapkey(VK_NUMPAD2    ,taa_KEY_NUMPAD_2);
        taa_window_mapkey(VK_NUMPAD3    ,taa_KEY_NUMPAD_3);
        taa_window_mapkey(VK_NUMPAD4    ,taa_KEY_NUMPAD_4);
        taa_window_mapkey(VK_NUMPAD5    ,taa_KEY_NUMPAD_5);
        taa_window_mapkey(VK_NUMPAD6    ,taa_KEY_NUMPAD_6);
        taa_window_mapkey(VK_NUMPAD7    ,taa_KEY_NUMPAD_7);
        taa_window_mapkey(VK_NUMPAD8    ,taa_KEY_NUMPAD_8);
        taa_window_mapkey(VK_NUMPAD9    ,taa_KEY_NUMPAD_9);
        taa_window_mapkey(VK_MULTIPLY   ,taa_KEY_NUMPAD_MULTIPLY);
        taa_window_mapkey(VK_ADD        ,taa_KEY_NUMPAD_ADD);
        taa_window_mapkey(VK_SEPARATOR  ,taa_KEY_NUMPAD_SEPARATOR);
        taa_window_mapkey(VK_SUBTRACT   ,taa_KEY_NUMPAD_SUBTRACT);
        taa_window_mapkey(VK_DECIMAL    ,taa_KEY_NUMPAD_DECIMAL);
        taa_window_mapkey(VK_DIVIDE     ,taa_KEY_NUMPAD_DIVIDE);
        taa_window_mapkey(VK_F1         ,taa_KEY_F1);
        taa_window_mapkey(VK_F2         ,taa_KEY_F2);
        taa_window_mapkey(VK_F3         ,taa_KEY_F3);
        taa_window_mapkey(VK_F4         ,taa_KEY_F4);
        taa_window_mapkey(VK_F5         ,taa_KEY_F5);
        taa_window_mapkey(VK_F6         ,taa_KEY_F6);
        taa_window_mapkey(VK_F7         ,taa_KEY_F7);
        taa_window_mapkey(VK_F8         ,taa_KEY_F8);
        taa_window_mapkey(VK_F9         ,taa_KEY_F9);
        taa_window_mapkey(VK_F10        ,taa_KEY_F10);
        taa_window_mapkey(VK_F11        ,taa_KEY_F11);
        taa_window_mapkey(VK_F12        ,taa_KEY_F12);
        taa_window_mapkey(VK_NUMLOCK    ,taa_KEY_NUMLOCK);
        taa_window_mapkey(VK_SCROLL     ,taa_KEY_SCROLL);
        taa_window_mapkey(VK_OEM_1      ,taa_KEY_SEMICOLON);
        taa_window_mapkey(VK_OEM_PLUS   ,taa_KEY_EQUAL);
        taa_window_mapkey(VK_OEM_COMMA  ,taa_KEY_COMMA);
        taa_window_mapkey(VK_OEM_MINUS  ,taa_KEY_MINUS);
        taa_window_mapkey(VK_OEM_PERIOD ,taa_KEY_PERIOD);
        taa_window_mapkey(VK_OEM_2      ,taa_KEY_SLASH);
        taa_window_mapkey(VK_OEM_3      ,taa_KEY_BACKQUOTE);
        taa_window_mapkey(VK_OEM_4      ,taa_KEY_LEFTBRACKET);
        taa_window_mapkey(VK_OEM_5      ,taa_KEY_BACKSLASH);
        taa_window_mapkey(VK_OEM_6      ,taa_KEY_RIGHTBRACKET);
        taa_window_mapkey(VK_OEM_7      ,taa_KEY_QUOTE);
        map = taa_s_window_keycodemap;
    }
    return (int32_t) map[vk & (taa_WINDOW_VKMAP_SIZE - 1)];
}

//****************************************************************************
static LRESULT CALLBACK taa_window_proc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    LONG_PTR wlptr = (LONG_PTR) GetWindowLongPtr(hWnd, GWL_USERDATA);
    taa_window_state* state = (taa_window_state*) wlptr;
    enum { MAX_EVENTS = sizeof(state->events)/sizeof(*state->events) };

    // NOTE: always check number of queued events, because this function may
    // be called recursively by DefWindowProc during dispatch of a single msg.
    // if too many events are received in a single frame, it just drops them.
    switch(uMsg)
    {
    case WM_ACTIVATE:
        // window activated / deactivated
        if(state->numevents < MAX_EVENTS)
        {
            taa_window_event* winevt;
            winevt = &state->events[state->numevents++];
            winevt->type = (HIWORD(wParam)) ?
                taa_WINDOW_EVENT_DEACTIVATE :
                taa_WINDOW_EVENT_ACTIVATE;
        }
        return 0;
    case WM_CLOSE:
        // window closed
        if(state->numevents < MAX_EVENTS)
        {
            taa_window_event* winevt;
            winevt = &state->events[state->numevents++];
            winevt->type = taa_WINDOW_EVENT_CLOSE;
        }
        return 0;
    case WM_CREATE:
        // window created
        {
            // attach the structure to the window
            wlptr = (LONG_PTR) ((LPCREATESTRUCT) lParam)->lpCreateParams;
#if _WIN64
            SetWindowLongPtr(hWnd,GWL_USERDATA, wlptr);
#else
            SetWindowLong(hWnd, GWL_USERDATA, (LONG) wlptr);
#endif
        }
        return 0;
    case WM_DESTROY:
        // window destroyed
        PostQuitMessage(0);
        return 0;
    case WM_KEYDOWN:
        // key is down
        {
            WORD ascii;
            BYTE kbState[256];
            int32_t key = taa_window_translatekey((int32_t) wParam);
            state->kbstate[key] = 1; // true
            GetKeyboardState(kbState);
            if(ToAscii((UINT)wParam, (UINT) lParam, kbState, &ascii, 0) != 1)
            {
                ascii = 0;
            }
            if(state->numevents < MAX_EVENTS)
            {
                taa_window_keyevent* keyevt;
                keyevt = &state->events[state->numevents++].key;
                keyevt->type = taa_WINDOW_EVENT_KEY_DOWN;
                keyevt->keycode = (uint8_t) key;
                keyevt->ascii = (char) ascii;
            }
        }
        return 0;
    case WM_KEYUP:
        // key is up
        {
            int32_t key = taa_window_translatekey((int32_t) wParam);
            state->kbstate[key] = 0; // false
            if(state->numevents < MAX_EVENTS)
            {
                taa_window_keyevent* keyevt;
                keyevt = &state->events[state->numevents++].key;
                keyevt->type = taa_WINDOW_EVENT_KEY_UP;
                keyevt->keycode = (uint8_t) key;
                keyevt->ascii = '\0';
            }
        }
        return 0;
    case WM_KILLFOCUS:
        // lost keyboard focus
        // clear keyboard state
        memset(state->kbstate, 0, sizeof(state->kbstate));
        state->mousestate.button1 = 0; // false
        state->mousestate.button2 = 0; // false
        state->mousestate.button3 = 0; // false
        ReleaseCapture(); // release the mouse
        return 0;
    case WM_LBUTTONDOWN:
        // left mouse down
        state->mousestate.cursorx = GET_X_LPARAM(lParam);
        state->mousestate.cursory = GET_Y_LPARAM(lParam);
        state->mousestate.button1 = 1; // true
        SetCapture(hWnd);
        if(state->numevents < MAX_EVENTS)
        {
            taa_window_mouseevent* mouseevt;
            mouseevt = &state->events[state->numevents++].mouse;
            mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON1_DOWN;
            mouseevt->state = state->mousestate;
        }
        return 0;
    case WM_LBUTTONUP:
        // left mouse up
        state->mousestate.cursorx = GET_X_LPARAM(lParam);
        state->mousestate.cursory = GET_Y_LPARAM(lParam);
        state->mousestate.button1 = 0; // false
        ReleaseCapture();
        if(state->numevents < MAX_EVENTS)
        {
            taa_window_mouseevent* mouseevt;
            mouseevt = &state->events[state->numevents++].mouse;
            mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON1_UP;
            mouseevt->state = state->mousestate;
        }
        return 0;
    case WM_MBUTTONDOWN:
        // middle mouse down
        state->mousestate.cursorx = GET_X_LPARAM(lParam);
        state->mousestate.cursory = GET_Y_LPARAM(lParam);
        state->mousestate.button2 = 1; // true
        SetCapture(hWnd);
        if(state->numevents < MAX_EVENTS)
        {
            taa_window_mouseevent* mouseevt;
            mouseevt = &state->events[state->numevents++].mouse;
            mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON2_DOWN;
            mouseevt->state = state->mousestate;
        }
        return 0;
    case WM_MBUTTONUP:
        // middle mouse up
        state->mousestate.cursorx = GET_X_LPARAM(lParam);
        state->mousestate.cursory = GET_Y_LPARAM(lParam);
        state->mousestate.button2 = 0; // false
        ReleaseCapture();
        if(state->numevents < MAX_EVENTS)
        {
            taa_window_mouseevent* mouseevt;
            mouseevt = &state->events[state->numevents++].mouse;
            mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON2_UP;
            mouseevt->state = state->mousestate;
        }
        return 0;
    case WM_MOUSEMOVE:
        // mouse moved
        state->mousestate.cursorx = GET_X_LPARAM(lParam);
        state->mousestate.cursory = GET_Y_LPARAM(lParam);
        state->mousestate.button1 = (wParam & MK_LBUTTON) != 0;
        state->mousestate.button2 = (wParam & MK_MBUTTON) != 0;
        state->mousestate.button3 = (wParam & MK_RBUTTON) != 0;
        if(state->numevents < MAX_EVENTS)
        {
            taa_window_mouseevent* mouseevt;
            mouseevt = &state->events[state->numevents++].mouse;
            mouseevt->type = taa_WINDOW_EVENT_MOUSE_MOVE;
            mouseevt->state = state->mousestate;
        }
        return 0;
    case WM_QUIT:
        // quit request
        if(state->numevents < MAX_EVENTS)
        {
            taa_window_event* winevt;
            winevt = &state->events[state->numevents++];
            winevt->type = taa_WINDOW_EVENT_CLOSE;
        }
        return 0;
    case WM_RBUTTONDOWN:
        // right mouse down
        state->mousestate.cursorx = GET_X_LPARAM(lParam);
        state->mousestate.cursory = GET_Y_LPARAM(lParam);
        state->mousestate.button3 = 1; // true
        SetCapture(hWnd);
        if(state->numevents < MAX_EVENTS)
        {
            taa_window_mouseevent* mouseevt;
            mouseevt = &state->events[state->numevents++].mouse;
            mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON3_DOWN;
            mouseevt->state = state->mousestate;
        }
        return 0;
    case WM_RBUTTONUP:
        // right mouse up
        state->mousestate.cursorx = GET_X_LPARAM(lParam);
        state->mousestate.cursory = GET_Y_LPARAM(lParam);
        state->mousestate.button3 = 0; // false
        ReleaseCapture();
        if(state->numevents < MAX_EVENTS)
        {
            taa_window_mouseevent* mouseevt;
            mouseevt = &state->events[state->numevents++].mouse;
            mouseevt->type = taa_WINDOW_EVENT_MOUSE_BUTTON3_UP;
            mouseevt->state = state->mousestate;
        }
        return 0;
    case WM_SIZE:
        // window resized
        state->width = LOWORD(lParam);
        state->height = HIWORD(lParam);
        if(state->numevents < MAX_EVENTS)
        {
            taa_window_event* winevt;
            winevt = &state->events[state->numevents++];
            winevt->type = taa_WINDOW_EVENT_SIZE;
        }
        return 0;
    case WM_SYSCOMMAND:
        // screensaver
        if(wParam == SC_SCREENSAVE || wParam == SC_MONITORPOWER)
        {
            // Prevent screen saver & monitor power save
            return 0;
        }
        break;
    }

    // Pass all unhandled messages to DefWindowProc
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//****************************************************************************
void taa_window_choosevisualinfo(
    taa_window_display* display,
    taa_window_visualinfo* viout)
{
    viout->win32 = 0;
}

//****************************************************************************
void taa_window_closedisplay(
    taa_window_display* disp)
{
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
    HINSTANCE hinstance;
    WNDCLASS wc;
    ATOM classid;
    HWND hwnd;
    RECT window_rect;
    DWORD dwExStyle;
    DWORD dwStyle;
    taa_window_state* state;

    state = (taa_window_state*) calloc(1, sizeof(*state));
    wout->win32.state = state;

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
    taa_CHECK_ERROR(classid, "Failed To Register The Window Class.");

    dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwStyle=WS_OVERLAPPEDWINDOW;

    window_rect.left = 0;
    window_rect.right = width;
    window_rect.top = 0;
    window_rect.bottom = height;
    AdjustWindowRectEx(&window_rect, dwStyle, FALSE, dwExStyle);

    // create the window.
    // "this" is passed as param to WM_CREATE
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
        state);
    taa_CHECK_ERROR(hwnd, "Window Creation Error.");

    wout->win32.hwnd = hwnd;
    wout->win32.classid = classid;
    wout->win32.state->width = width;
    wout->win32.state->height = height;
    wout->win32.state->numevents = 0;

    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}

//****************************************************************************
void taa_window_destroy(
    taa_window* w)
{
    // Destroy the window
    int32_t r = DestroyWindow(w->win32.hwnd);
    taa_CHECK_ERROR(r, "Could Not Release hWnd.");

    if(w->win32.classid)
    {
        // Unregister the class
        ATOM classid = w->win32.classid;
        r = UnregisterClass(MAKEINTATOM(classid), GetModuleHandle(NULL));
        taa_CHECK_ERROR(r, "Could Not Unregister Class.");
    }
    free(w->win32.state);
}

//****************************************************************************
void taa_window_opendisplay(
    taa_window_display* dispout)
{
    dispout->win32 = 0;
}

//****************************************************************************
void taa_window_show(
    taa_window* w,
    int32_t visible)
{
    ShowWindow(w->win32.hwnd, (visible) ? SW_SHOW : SW_HIDE);
}

//****************************************************************************
void taa_window_update(
    taa_window* w,
    taa_window_state* stateout)
{
    taa_window_state* state = w->win32.state;
    int32_t *numevents = &state->numevents;
    MSG msg;

    *numevents = 0;
    while((*numevents) < (sizeof(state->events)/sizeof(*state->events)))
    {
        if(!PeekMessage(&msg, w->win32.hwnd, 0, 0, PM_REMOVE))
        {
            break;
        }

        if (msg.message == WM_QUIT)
        {
            taa_window_event* winevt = &state->events[(*numevents)++];
            winevt->type = taa_WINDOW_EVENT_CLOSE;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    assert((*numevents) <= (sizeof(state->events)/sizeof(*state->events)));

    if(stateout != NULL)
    {
        *stateout = *state;
    }
}

#endif // TAA_WINDOW_C_
