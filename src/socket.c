/**
 * @brief     target agnostic socket implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#define taa_SOCKET_C_

#ifdef WIN32
#include "socket_win32.c"
#else
#include "socket_posix.c"
#endif 

#undef taa_SOCKET_C_
