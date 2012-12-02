/**
 * @brief     miscellaneous system function header for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_SYSTEM_WIN32_H_
#define taa_SYSTEM_WIN32_H_

// 0x501 or higher required for ConvertFiberToThread
#define _WIN32_WINNT 0x0501
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

enum
{
    taa_S_IFREG_TARGET = 1,
    taa_S_IFDIR_TARGET = 2
};

#endif // taa_SYSTEM_WIN32_H_
