/**
 * @brief     miscellaneous system function header for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_SYSTEM_WIN32_H_
#define TAA_SYSTEM_WIN32_H_

// 0x501 or higher required for ConvertFiberToThread
#define _WIN32_WINNT 0x0501
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <io.h>

typedef struct taa_dir_win32_s taa_dir_win32;

struct taa_dir_win32_s
{
    intptr_t h;
    char* name;
    struct _finddata_t data;
};

struct taa_dir_s
{
    taa_dir_win32 win32;
};

#endif // TAA_SYSTEM_WIN32_H_
