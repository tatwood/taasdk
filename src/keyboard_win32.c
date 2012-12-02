/**
 * @brief     keyboard input implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by keyboard.c
#ifdef taa_KEYBOARD_C_
#include <taa/keyboard.h>
#include <assert.h>
#include <string.h>

enum
{
    taa_KEYBOARD_VKMAPSIZE = 256
};

//****************************************************************************
static void taa_keyboard_mapkey(
    uint8_t* map,
    uint32_t vk,
    uint8_t key)
{
    assert((vk & (taa_KEYBOARD_VKMAPSIZE-1)) == vk);
    assert(map[vk] == taa_KEY_UNKNOWN);
    map[vk] = key;
}

//****************************************************************************
static uint8_t* taa_keyboard_init()
{
    static uint8_t map[taa_KEYBOARD_VKMAPSIZE];
    int32_t i;
    for(i = 0; i < taa_KEYBOARD_VKMAPSIZE; ++i)
    {
        map[i] = taa_KEY_UNKNOWN;
    }
    //taa_keyboard_mapkey(map, VK_LBUTTON    ,taa_KEY_BUTTON1);
    //taa_keyboard_mapkey(map, VK_RBUTTON    ,taa_KEY_BUTTON2);
    //taa_keyboard_mapkey(map, VK_MBUTTON    ,taa_KEY_BUTTON3);
    taa_keyboard_mapkey(map, VK_BACK       ,taa_KEY_BACKSPACE);
    taa_keyboard_mapkey(map, VK_TAB        ,taa_KEY_TAB);
    taa_keyboard_mapkey(map, VK_RETURN     ,taa_KEY_ENTER);
    taa_keyboard_mapkey(map, VK_PAUSE      ,taa_KEY_PAUSE);
    taa_keyboard_mapkey(map, VK_CAPITAL    ,taa_KEY_CAPSLOCK);
    taa_keyboard_mapkey(map, VK_ESCAPE     ,taa_KEY_ESCAPE);
    taa_keyboard_mapkey(map, VK_SPACE      ,taa_KEY_SPACE);
    taa_keyboard_mapkey(map, VK_PRIOR      ,taa_KEY_PAGE_UP);
    taa_keyboard_mapkey(map, VK_NEXT       ,taa_KEY_PAGE_DOWN);
    taa_keyboard_mapkey(map, VK_END        ,taa_KEY_END);
    taa_keyboard_mapkey(map, VK_HOME       ,taa_KEY_HOME);
    taa_keyboard_mapkey(map, VK_LEFT       ,taa_KEY_LEFT);
    taa_keyboard_mapkey(map, VK_UP         ,taa_KEY_UP);
    taa_keyboard_mapkey(map, VK_RIGHT      ,taa_KEY_RIGHT);
    taa_keyboard_mapkey(map, VK_DOWN       ,taa_KEY_DOWN);
    taa_keyboard_mapkey(map, VK_SNAPSHOT   ,taa_KEY_PRINTSCREEN);
    taa_keyboard_mapkey(map, VK_INSERT     ,taa_KEY_INSERT);
    taa_keyboard_mapkey(map, VK_DELETE     ,taa_KEY_DELETE);
    taa_keyboard_mapkey(map, '0'           ,taa_KEY_0);
    taa_keyboard_mapkey(map, '1'           ,taa_KEY_1);
    taa_keyboard_mapkey(map, '2'           ,taa_KEY_2);
    taa_keyboard_mapkey(map, '3'           ,taa_KEY_3);
    taa_keyboard_mapkey(map, '4'           ,taa_KEY_4);
    taa_keyboard_mapkey(map, '5'           ,taa_KEY_5);
    taa_keyboard_mapkey(map, '6'           ,taa_KEY_6);
    taa_keyboard_mapkey(map, '7'           ,taa_KEY_7);
    taa_keyboard_mapkey(map, '8'           ,taa_KEY_8);
    taa_keyboard_mapkey(map, '9'           ,taa_KEY_9);
    taa_keyboard_mapkey(map, 'A'           ,taa_KEY_A);
    taa_keyboard_mapkey(map, 'B'           ,taa_KEY_B);
    taa_keyboard_mapkey(map, 'C'           ,taa_KEY_C);
    taa_keyboard_mapkey(map, 'D'           ,taa_KEY_D);
    taa_keyboard_mapkey(map, 'E'           ,taa_KEY_E);
    taa_keyboard_mapkey(map, 'F'           ,taa_KEY_F);
    taa_keyboard_mapkey(map, 'G'           ,taa_KEY_G);
    taa_keyboard_mapkey(map, 'H'           ,taa_KEY_H);
    taa_keyboard_mapkey(map, 'I'           ,taa_KEY_I);
    taa_keyboard_mapkey(map, 'J'           ,taa_KEY_J);
    taa_keyboard_mapkey(map, 'K'           ,taa_KEY_K);
    taa_keyboard_mapkey(map, 'L'           ,taa_KEY_L);
    taa_keyboard_mapkey(map, 'M'           ,taa_KEY_M);
    taa_keyboard_mapkey(map, 'N'           ,taa_KEY_N);
    taa_keyboard_mapkey(map, 'O'           ,taa_KEY_O);
    taa_keyboard_mapkey(map, 'P'           ,taa_KEY_P);
    taa_keyboard_mapkey(map, 'Q'           ,taa_KEY_Q);
    taa_keyboard_mapkey(map, 'R'           ,taa_KEY_R);
    taa_keyboard_mapkey(map, 'S'           ,taa_KEY_S);
    taa_keyboard_mapkey(map, 'T'           ,taa_KEY_T);
    taa_keyboard_mapkey(map, 'U'           ,taa_KEY_U);
    taa_keyboard_mapkey(map, 'V'           ,taa_KEY_V);
    taa_keyboard_mapkey(map, 'W'           ,taa_KEY_W);
    taa_keyboard_mapkey(map, 'X'           ,taa_KEY_X);
    taa_keyboard_mapkey(map, 'Y'           ,taa_KEY_Y);
    taa_keyboard_mapkey(map, 'Z'           ,taa_KEY_Z);
    taa_keyboard_mapkey(map, VK_LWIN       ,taa_KEY_LWIN);
    taa_keyboard_mapkey(map, VK_RWIN       ,taa_KEY_RWIN);
    taa_keyboard_mapkey(map, VK_APPS       ,taa_KEY_APPLICATION);
    taa_keyboard_mapkey(map, VK_NUMPAD0    ,taa_KEY_NUMPAD_0);
    taa_keyboard_mapkey(map, VK_NUMPAD1    ,taa_KEY_NUMPAD_1);
    taa_keyboard_mapkey(map, VK_NUMPAD2    ,taa_KEY_NUMPAD_2);
    taa_keyboard_mapkey(map, VK_NUMPAD3    ,taa_KEY_NUMPAD_3);
    taa_keyboard_mapkey(map, VK_NUMPAD4    ,taa_KEY_NUMPAD_4);
    taa_keyboard_mapkey(map, VK_NUMPAD5    ,taa_KEY_NUMPAD_5);
    taa_keyboard_mapkey(map, VK_NUMPAD6    ,taa_KEY_NUMPAD_6);
    taa_keyboard_mapkey(map, VK_NUMPAD7    ,taa_KEY_NUMPAD_7);
    taa_keyboard_mapkey(map, VK_NUMPAD8    ,taa_KEY_NUMPAD_8);
    taa_keyboard_mapkey(map, VK_NUMPAD9    ,taa_KEY_NUMPAD_9);
    taa_keyboard_mapkey(map, VK_MULTIPLY   ,taa_KEY_NUMPAD_MULTIPLY);
    taa_keyboard_mapkey(map, VK_ADD        ,taa_KEY_NUMPAD_ADD);
    taa_keyboard_mapkey(map, VK_SEPARATOR  ,taa_KEY_NUMPAD_SEPARATOR);
    taa_keyboard_mapkey(map, VK_SUBTRACT   ,taa_KEY_NUMPAD_SUBTRACT);
    taa_keyboard_mapkey(map, VK_DECIMAL    ,taa_KEY_NUMPAD_DECIMAL);
    taa_keyboard_mapkey(map, VK_DIVIDE     ,taa_KEY_NUMPAD_DIVIDE);
    taa_keyboard_mapkey(map, VK_F1         ,taa_KEY_F1);
    taa_keyboard_mapkey(map, VK_F2         ,taa_KEY_F2);
    taa_keyboard_mapkey(map, VK_F3         ,taa_KEY_F3);
    taa_keyboard_mapkey(map, VK_F4         ,taa_KEY_F4);
    taa_keyboard_mapkey(map, VK_F5         ,taa_KEY_F5);
    taa_keyboard_mapkey(map, VK_F6         ,taa_KEY_F6);
    taa_keyboard_mapkey(map, VK_F7         ,taa_KEY_F7);
    taa_keyboard_mapkey(map, VK_F8         ,taa_KEY_F8);
    taa_keyboard_mapkey(map, VK_F9         ,taa_KEY_F9);
    taa_keyboard_mapkey(map, VK_F10        ,taa_KEY_F10);
    taa_keyboard_mapkey(map, VK_F11        ,taa_KEY_F11);
    taa_keyboard_mapkey(map, VK_F12        ,taa_KEY_F12);
    taa_keyboard_mapkey(map, VK_NUMLOCK    ,taa_KEY_NUMLOCK);
    taa_keyboard_mapkey(map, VK_SCROLL     ,taa_KEY_SCROLL);
    taa_keyboard_mapkey(map, VK_LSHIFT     ,taa_KEY_LSHIFT);
    taa_keyboard_mapkey(map, VK_RSHIFT     ,taa_KEY_RSHIFT);
    taa_keyboard_mapkey(map, VK_LCONTROL   ,taa_KEY_LCTRL);
    taa_keyboard_mapkey(map, VK_RCONTROL   ,taa_KEY_RCTRL);
    taa_keyboard_mapkey(map, VK_LMENU      ,taa_KEY_LALT);
    taa_keyboard_mapkey(map, VK_RMENU      ,taa_KEY_RALT);
    taa_keyboard_mapkey(map, VK_OEM_1      ,taa_KEY_SEMICOLON);
    taa_keyboard_mapkey(map, VK_OEM_PLUS   ,taa_KEY_EQUAL);
    taa_keyboard_mapkey(map, VK_OEM_COMMA  ,taa_KEY_COMMA);
    taa_keyboard_mapkey(map, VK_OEM_MINUS  ,taa_KEY_MINUS);
    taa_keyboard_mapkey(map, VK_OEM_PERIOD ,taa_KEY_PERIOD);
    taa_keyboard_mapkey(map, VK_OEM_2      ,taa_KEY_SLASH);
    taa_keyboard_mapkey(map, VK_OEM_3      ,taa_KEY_BACKQUOTE);
    taa_keyboard_mapkey(map, VK_OEM_4      ,taa_KEY_LEFTBRACKET);
    taa_keyboard_mapkey(map, VK_OEM_5      ,taa_KEY_BACKSLASH);
    taa_keyboard_mapkey(map, VK_OEM_6      ,taa_KEY_RIGHTBRACKET);
    taa_keyboard_mapkey(map, VK_OEM_7      ,taa_KEY_QUOTE);
    return map;
}

//****************************************************************************
void taa_keyboard_query(
    taa_window_display disp,
    taa_keyboard_state* kb_out)
{
    uint8_t* kb = kb_out->keys;
    BYTE vkstate[256];
    int32_t vk;
    GetKeyboardState(vkstate);
    memset(kb_out, 0, sizeof(taa_keyboard_state));
    for(vk = 0; vk < taa_KEYBOARD_VKMAPSIZE; ++vk)
    {
        uint8_t keycode = taa_keyboard_translate(disp, vk);
        if(keycode != taa_KEY_UNKNOWN)
        {
            kb[keycode] = (vkstate[vk]  & 0x80) != 0;
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
        map = taa_keyboard_init();
    }
    return (uint8_t) map[keycode & (taa_KEYBOARD_VKMAPSIZE - 1)];
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
