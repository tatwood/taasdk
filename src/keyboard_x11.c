/**
 * @brief     keyboard input implementation for X11
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by keyboard.c
#ifdef taa_KEYBOARD_C_
#include <taa/keyboard.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <assert.h>
#include <string.h>

enum
{
    taa_KEYBOARD_XKMAPSIZE = 256
};

//****************************************************************************
static void taa_keyboard_mapkey(
    uint8_t* map,
    Display* d,
    KeySym ks,
    uint8_t key)
{
    uint8_t xcode = XKeysymToKeycode(d, ks);
    assert((xcode & 0xff) ==  xcode);
    assert(map[xcode] == taa_KEY_UNKNOWN);
    map[xcode] = key;
}

//****************************************************************************
static uint8_t* taa_keyboard_init(Display* d)
{
    static uint8_t map[taa_KEYBOARD_XKMAPSIZE];
    int32_t i;
    for(i = 0; i < taa_KEYBOARD_XKMAPSIZE; ++i)
    {
        map[i] = taa_KEY_UNKNOWN;
    }
    //taa_keyboard_mapkey(map,d,XK_Pointer_Button1 ,taa_KEY_BUTTON1);
    //taa_keyboard_mapkey(map,d,XK_Pointer_Button2 ,taa_KEY_BUTTON2);
    //taa_keyboard_mapkey(map,d,XK_Pointer_Button3 ,taa_KEY_BUTTON3);
    taa_keyboard_mapkey(map,d,XK_BackSpace       ,taa_KEY_BACKSPACE);
    taa_keyboard_mapkey(map,d,XK_Tab             ,taa_KEY_TAB);
    taa_keyboard_mapkey(map,d,XK_Return          ,taa_KEY_ENTER);
    taa_keyboard_mapkey(map,d,XK_Pause           ,taa_KEY_PAUSE);
    taa_keyboard_mapkey(map,d,XK_Caps_Lock       ,taa_KEY_CAPSLOCK);
    taa_keyboard_mapkey(map,d,XK_Escape          ,taa_KEY_ESCAPE);
    taa_keyboard_mapkey(map,d,XK_space           ,taa_KEY_SPACE);
    taa_keyboard_mapkey(map,d,XK_Prior           ,taa_KEY_PAGE_UP);
    taa_keyboard_mapkey(map,d,XK_Next            ,taa_KEY_PAGE_DOWN);
    taa_keyboard_mapkey(map,d,XK_End             ,taa_KEY_END);
    taa_keyboard_mapkey(map,d,XK_Home            ,taa_KEY_HOME);
    taa_keyboard_mapkey(map,d,XK_Left            ,taa_KEY_LEFT);
    taa_keyboard_mapkey(map,d,XK_Up              ,taa_KEY_UP);
    taa_keyboard_mapkey(map,d,XK_Right           ,taa_KEY_RIGHT);
    taa_keyboard_mapkey(map,d,XK_Down            ,taa_KEY_DOWN);
    taa_keyboard_mapkey(map,d,XK_Print           ,taa_KEY_PRINTSCREEN);
    taa_keyboard_mapkey(map,d,XK_Insert          ,taa_KEY_INSERT);
    taa_keyboard_mapkey(map,d,XK_Delete          ,taa_KEY_DELETE);
    taa_keyboard_mapkey(map,d,'0'                ,taa_KEY_0);
    taa_keyboard_mapkey(map,d,'1'                ,taa_KEY_1);
    taa_keyboard_mapkey(map,d,'2'                ,taa_KEY_2);
    taa_keyboard_mapkey(map,d,'3'                ,taa_KEY_3);
    taa_keyboard_mapkey(map,d,'4'                ,taa_KEY_4);
    taa_keyboard_mapkey(map,d,'5'                ,taa_KEY_5);
    taa_keyboard_mapkey(map,d,'6'                ,taa_KEY_6);
    taa_keyboard_mapkey(map,d,'7'                ,taa_KEY_7);
    taa_keyboard_mapkey(map,d,'8'                ,taa_KEY_8);
    taa_keyboard_mapkey(map,d,'9'                ,taa_KEY_9);
    taa_keyboard_mapkey(map,d,'a'                ,taa_KEY_A);
    taa_keyboard_mapkey(map,d,'b'                ,taa_KEY_B);
    taa_keyboard_mapkey(map,d,'c'                ,taa_KEY_C);
    taa_keyboard_mapkey(map,d,'d'                ,taa_KEY_D);
    taa_keyboard_mapkey(map,d,'e'                ,taa_KEY_E);
    taa_keyboard_mapkey(map,d,'f'                ,taa_KEY_F);
    taa_keyboard_mapkey(map,d,'g'                ,taa_KEY_G);
    taa_keyboard_mapkey(map,d,'h'                ,taa_KEY_H);
    taa_keyboard_mapkey(map,d,'i'                ,taa_KEY_I);
    taa_keyboard_mapkey(map,d,'j'                ,taa_KEY_J);
    taa_keyboard_mapkey(map,d,'k'                ,taa_KEY_K);
    taa_keyboard_mapkey(map,d,'l'                ,taa_KEY_L);
    taa_keyboard_mapkey(map,d,'m'                ,taa_KEY_M);
    taa_keyboard_mapkey(map,d,'n'                ,taa_KEY_N);
    taa_keyboard_mapkey(map,d,'o'                ,taa_KEY_O);
    taa_keyboard_mapkey(map,d,'p'                ,taa_KEY_P);
    taa_keyboard_mapkey(map,d,'q'                ,taa_KEY_Q);
    taa_keyboard_mapkey(map,d,'r'                ,taa_KEY_R);
    taa_keyboard_mapkey(map,d,'s'                ,taa_KEY_S);
    taa_keyboard_mapkey(map,d,'t'                ,taa_KEY_T);
    taa_keyboard_mapkey(map,d,'u'                ,taa_KEY_U);
    taa_keyboard_mapkey(map,d,'v'                ,taa_KEY_V);
    taa_keyboard_mapkey(map,d,'w'                ,taa_KEY_W);
    taa_keyboard_mapkey(map,d,'x'                ,taa_KEY_X);
    taa_keyboard_mapkey(map,d,'y'                ,taa_KEY_Y);
    taa_keyboard_mapkey(map,d,'z'                ,taa_KEY_Z);
    taa_keyboard_mapkey(map,d,XK_Super_L         ,taa_KEY_LWIN);
    taa_keyboard_mapkey(map,d,XK_Super_R         ,taa_KEY_RWIN);
    taa_keyboard_mapkey(map,d,XK_Menu            ,taa_KEY_APPLICATION);
    taa_keyboard_mapkey(map,d,XK_KP_0            ,taa_KEY_NUMPAD_0);
    taa_keyboard_mapkey(map,d,XK_KP_1            ,taa_KEY_NUMPAD_1);
    taa_keyboard_mapkey(map,d,XK_KP_2            ,taa_KEY_NUMPAD_2);
    taa_keyboard_mapkey(map,d,XK_KP_3            ,taa_KEY_NUMPAD_3);
    taa_keyboard_mapkey(map,d,XK_KP_4            ,taa_KEY_NUMPAD_4);
    taa_keyboard_mapkey(map,d,XK_KP_5            ,taa_KEY_NUMPAD_5);
    taa_keyboard_mapkey(map,d,XK_KP_6            ,taa_KEY_NUMPAD_6);
    taa_keyboard_mapkey(map,d,XK_KP_7            ,taa_KEY_NUMPAD_7);
    taa_keyboard_mapkey(map,d,XK_KP_8            ,taa_KEY_NUMPAD_8);
    taa_keyboard_mapkey(map,d,XK_KP_9            ,taa_KEY_NUMPAD_9);
    taa_keyboard_mapkey(map,d,XK_KP_Multiply     ,taa_KEY_NUMPAD_MULTIPLY);
    taa_keyboard_mapkey(map,d,XK_KP_Add          ,taa_KEY_NUMPAD_ADD);
    taa_keyboard_mapkey(map,d,XK_KP_Separator    ,taa_KEY_NUMPAD_SEPARATOR);
    taa_keyboard_mapkey(map,d,XK_KP_Subtract     ,taa_KEY_NUMPAD_SUBTRACT);
    taa_keyboard_mapkey(map,d,XK_KP_Decimal      ,taa_KEY_NUMPAD_DECIMAL);
    taa_keyboard_mapkey(map,d,XK_KP_Divide       ,taa_KEY_NUMPAD_DIVIDE);
    taa_keyboard_mapkey(map,d,XK_F1              ,taa_KEY_F1);
    taa_keyboard_mapkey(map,d,XK_F2              ,taa_KEY_F2);
    taa_keyboard_mapkey(map,d,XK_F3              ,taa_KEY_F3);
    taa_keyboard_mapkey(map,d,XK_F4              ,taa_KEY_F4);
    taa_keyboard_mapkey(map,d,XK_F5              ,taa_KEY_F5);
    taa_keyboard_mapkey(map,d,XK_F6              ,taa_KEY_F6);
    taa_keyboard_mapkey(map,d,XK_F7              ,taa_KEY_F7);
    taa_keyboard_mapkey(map,d,XK_F8              ,taa_KEY_F8);
    taa_keyboard_mapkey(map,d,XK_F9              ,taa_KEY_F9);
    taa_keyboard_mapkey(map,d,XK_F10             ,taa_KEY_F10);
    taa_keyboard_mapkey(map,d,XK_F11             ,taa_KEY_F11);
    taa_keyboard_mapkey(map,d,XK_F12             ,taa_KEY_F12);
    taa_keyboard_mapkey(map,d,XK_Num_Lock        ,taa_KEY_NUMLOCK);
    taa_keyboard_mapkey(map,d,XK_Scroll_Lock     ,taa_KEY_SCROLL);
    taa_keyboard_mapkey(map,d,XK_Shift_L         ,taa_KEY_LSHIFT);
    taa_keyboard_mapkey(map,d,XK_Shift_R         ,taa_KEY_RSHIFT);
    taa_keyboard_mapkey(map,d,XK_Control_L       ,taa_KEY_LCTRL);
    taa_keyboard_mapkey(map,d,XK_Control_R       ,taa_KEY_RCTRL);
    taa_keyboard_mapkey(map,d,XK_Alt_L           ,taa_KEY_LALT);
    taa_keyboard_mapkey(map,d,XK_Alt_R           ,taa_KEY_RALT);
    taa_keyboard_mapkey(map,d,XK_semicolon       ,taa_KEY_SEMICOLON);
    taa_keyboard_mapkey(map,d,XK_equal           ,taa_KEY_EQUAL);
    taa_keyboard_mapkey(map,d,XK_comma           ,taa_KEY_COMMA);
    taa_keyboard_mapkey(map,d,XK_minus           ,taa_KEY_MINUS);
    taa_keyboard_mapkey(map,d,XK_period          ,taa_KEY_PERIOD);
    taa_keyboard_mapkey(map,d,XK_slash           ,taa_KEY_SLASH);
    taa_keyboard_mapkey(map,d,XK_grave           ,taa_KEY_BACKQUOTE);
    taa_keyboard_mapkey(map,d,XK_bracketleft     ,taa_KEY_LEFTBRACKET);
    taa_keyboard_mapkey(map,d,XK_backslash       ,taa_KEY_BACKSLASH);
    taa_keyboard_mapkey(map,d,XK_bracketright    ,taa_KEY_RIGHTBRACKET);
    taa_keyboard_mapkey(map,d,XK_apostrophe      ,taa_KEY_QUOTE);
    return map;
}

//****************************************************************************
void taa_keyboard_query(
    taa_window_display disp,
    taa_keyboard_state* kb_out)
{
    uint8_t* kb = kb_out->keys;
    char xkbits[32];
    int32_t xk;
    uint32_t bit;
    uint32_t byte;
    XQueryKeymap((Display*) disp, xkbits);
    memset(kb_out, 0, sizeof(taa_keyboard_state));
    bit = 1;
    byte = 0;
    for(xk = 0; xk < taa_KEYBOARD_XKMAPSIZE; ++xk)
    {
        uint8_t keycode = taa_keyboard_translate(disp, xk);
        if(keycode != taa_KEY_UNKNOWN)
        {
            kb[keycode] = ((xkbits[byte] & bit) != 0) ? 1 : 0;
        }
        bit <<= 1;
        if(bit >= 256)
        {
            bit = 1;
            ++byte;
        }
    }
}

//****************************************************************************
uint8_t taa_keyboard_translate(
    taa_window_display disp,
    int32_t keycode)
{
    static uint8_t* map = NULL;
    if(map == NULL)
    {
        map = taa_keyboard_init((Display*) disp);
    }
    return (uint8_t) map[keycode & (taa_KEYBOARD_XKMAPSIZE - 1)];
}

//****************************************************************************
void taa_keyboard_update(
    const taa_window_event* events,
    uint32_t numevents,
    taa_keyboard_state* kb_out)
{
    uint8_t* kb = kb_out->keys;
    const taa_window_event* evtitr = events;
    const taa_window_event* evtend = evtitr + numevents;
    while(evtitr != evtend)
    {
        switch(evtitr->type)
        {
        case taa_WINDOW_EVENT_DEACTIVATE:
            // if lost focus, clear the entire table
            memset(kb, 0, sizeof(taa_keyboard_state));
            break;
        case taa_WINDOW_EVENT_KEY_DOWN:
            kb[evtitr->key.keycode] = 1;
            break;
        case taa_WINDOW_EVENT_KEY_UP:
            kb[evtitr->key.keycode] = 0;
            break;
        default:
            break;
        }
        ++evtitr;
    }
}

#endif // taa_KEYBOARD_C_
