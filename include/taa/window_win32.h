/**
 * @brief     window management header for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_WINDOW_WIN32_H_
#define TAA_WINDOW_WIN32_H_

typedef struct taa_window_win32_s taa_window_win32;

struct taa_window_win32_s
{
    HWND hwnd;
    ATOM classid;
    taa_window_state* state;
};

struct taa_window_display_s
{
    int32_t win32;
};

struct taa_window_visualinfo_s
{
    int32_t win32;
};

struct taa_window_s
{
    taa_window_win32 win32;
};

#endif // TAA_WINDOW_WIN32_H_
