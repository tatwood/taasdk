/**
 * @brief     target agnostic header for keyboard input
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_KEYBOARD_H_
#define taa_KEYBOARD_H_

#include "window.h"

//****************************************************************************
// enums

enum taa_keyboard_keycode_e
{
    //taa_KEY_BUTTON1         =   1, // left mouse button
    //taa_KEY_BUTTON2         =   2, // right mouse button
    //taa_KEY_BUTTON3         =   4, // middle mouse button
    taa_KEY_BACKSPACE       =   8, // Backspace key
    taa_KEY_TAB             =   9, // Tab key
    taa_KEY_ENTER           =  13, // Enter key
    taa_KEY_PAUSE           =  19, // Pause Break key
    taa_KEY_CAPSLOCK        =  20, // Caps Lock key
    taa_KEY_ESCAPE          =  27, // Escape key
    taa_KEY_SPACE           =  32, // Spacebar
    taa_KEY_PAGE_UP         =  33, // Page Up key
    taa_KEY_PAGE_DOWN       =  34, // Page Down key
    taa_KEY_END             =  35, // End key
    taa_KEY_HOME            =  36, // Home key
    taa_KEY_LEFT            =  37, // Left Arrow key
    taa_KEY_UP              =  38, // Up Arrow key
    taa_KEY_RIGHT           =  39, // Right Arrow key
    taa_KEY_DOWN            =  40, // Down Arrow key
    taa_KEY_PRINTSCREEN     =  44, // Print Screen key
    taa_KEY_INSERT          =  45, // Insert key
    taa_KEY_DELETE          =  46, // Delete key
    taa_KEY_0               =  48, // 0) key
    taa_KEY_1               =  49, // 1! key
    taa_KEY_2               =  50, // 2@ key
    taa_KEY_3               =  51, // 3# key
    taa_KEY_4               =  52, // 4$ key
    taa_KEY_5               =  53, // 5% key
    taa_KEY_6               =  54, // 6^ key
    taa_KEY_7               =  55, // 7& key
    taa_KEY_8               =  56, // 8* key
    taa_KEY_9               =  57, // 9( key
    taa_KEY_A               =  65, // A key
    taa_KEY_B               =  66, // B key
    taa_KEY_C               =  67, // C key
    taa_KEY_D               =  68, // D key
    taa_KEY_E               =  69, // E key
    taa_KEY_F               =  70, // F key
    taa_KEY_G               =  71, // G key
    taa_KEY_H               =  72, // H key
    taa_KEY_I               =  73, // I key
    taa_KEY_J               =  74, // J key
    taa_KEY_K               =  75, // K key
    taa_KEY_L               =  76, // L key
    taa_KEY_M               =  77, // M key
    taa_KEY_N               =  78, // N key
    taa_KEY_O               =  79, // O key
    taa_KEY_P               =  80, // P key
    taa_KEY_Q               =  81, // Q key
    taa_KEY_R               =  82, // R key
    taa_KEY_S               =  83, // S key
    taa_KEY_T               =  84, // T key
    taa_KEY_U               =  85, // U key
    taa_KEY_V               =  86, // V key
    taa_KEY_W               =  87, // W key
    taa_KEY_X               =  88, // X key
    taa_KEY_Y               =  89, // Y key
    taa_KEY_Z               =  90, // Z key
    taa_KEY_LWIN            =  91, // Left taa_windows (super) key
    taa_KEY_RWIN            =  91, // Right taa_windows (super) key
    taa_KEY_APPLICATION     =  93, // Application key
    taa_KEY_NUMPAD_0        =  96, // 0 key on num pad
    taa_KEY_NUMPAD_1        =  97, // 1 key on num pad
    taa_KEY_NUMPAD_2        =  98, // 2 key on num pad
    taa_KEY_NUMPAD_3        =  99, // 3 key on num pad
    taa_KEY_NUMPAD_4        = 100, // 4 key on num pad
    taa_KEY_NUMPAD_5        = 101, // 5 key on num pad
    taa_KEY_NUMPAD_6        = 102, // 6 key on num pad
    taa_KEY_NUMPAD_7        = 103, // 7 key on num pad
    taa_KEY_NUMPAD_8        = 104, // 8 key on num pad
    taa_KEY_NUMPAD_9        = 105, // 9 key on num pad
    taa_KEY_NUMPAD_MULTIPLY = 106, // Multiply key on num pad
    taa_KEY_NUMPAD_ADD      = 107, // Add key on num pad
    taa_KEY_NUMPAD_SEPARATOR= 108, // Separator key on num pad (comma)
    taa_KEY_NUMPAD_SUBTRACT = 109, // Subtract key on num pad
    taa_KEY_NUMPAD_DECIMAL  = 110, // Decimal key on num pad
    taa_KEY_NUMPAD_DIVIDE   = 111, // Divide key on num pad
    taa_KEY_F1              = 112, // F1 key
    taa_KEY_F2              = 113, // F2 key
    taa_KEY_F3              = 114, // F3 key
    taa_KEY_F4              = 115, // F4 key
    taa_KEY_F5              = 116, // F5 key
    taa_KEY_F6              = 117, // F6 key
    taa_KEY_F7              = 118, // F7 key
    taa_KEY_F8              = 119, // F8 key
    taa_KEY_F9              = 120, // F9 key
    taa_KEY_F10             = 121, // F10 key
    taa_KEY_F11             = 122, // F11 key
    taa_KEY_F12             = 123, // F12 key
    taa_KEY_NUMLOCK         = 144, // Num Lock key
    taa_KEY_SCROLL          = 145, // Scroll Lock key
    taa_KEY_LSHIFT          = 160, // left shift key
    taa_KEY_RSHIFT          = 161, // right shift key
    taa_KEY_LCTRL           = 162, // left control key
    taa_KEY_RCTRL           = 163, // right control key
    taa_KEY_LALT            = 164, // left alt (option) key
    taa_KEY_RALT            = 165, // left alt (option) key
    taa_KEY_SEMICOLON       = 186, // ;: key
    taa_KEY_EQUAL           = 187, // =+ key
    taa_KEY_COMMA           = 188, // ,< key
    taa_KEY_MINUS           = 189, // -_ key
    taa_KEY_PERIOD          = 190, // .> key
    taa_KEY_SLASH           = 191, // /? key
    taa_KEY_BACKQUOTE       = 192, // `~ key
    taa_KEY_LEFTBRACKET     = 219, // [{ key
    taa_KEY_BACKSLASH       = 220, // \| key
    taa_KEY_RIGHTBRACKET    = 221, // ]} key
    taa_KEY_QUOTE           = 222, // '" key
    taa_KEY_UNKNOWN         = 255
};

//****************************************************************************
// typedefs

typedef enum taa_keyboard_keycode_e taa_keyboard_keycode;

typedef struct taa_keyboard_state_s taa_keyboard_state;

//****************************************************************************
// structs

struct taa_keyboard_state_s
{
    uint8_t keys[256];
};

//****************************************************************************
// functions

taa_SDK_LINKAGE void taa_keyboard_query(
    taa_window_display disp,
    taa_keyboard_state* kb_out);

/**
 * translates a native key code into a cross platform value
 * @param disp handle to the display connection
 * @param keycode On X11 this is a KeyCode. On win32 it is a VK code
 * @return the matching taa_keyboard_keycode
 */
taa_SDK_LINKAGE uint8_t taa_keyboard_translate(
    taa_window_display disp,
    int32_t keycode);

/**
 * updates an existing keyboard state based on a set of window events
 */
taa_SDK_LINKAGE void taa_keyboard_update(
    const taa_window_event* events,
    uint32_t numevents,
    taa_keyboard_state* kb);

#endif // taa_KEYBOARD_H_
