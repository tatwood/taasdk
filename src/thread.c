/**
 * @brief     target agnostic wrapper thread management implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/thread.h>

#define TAA_THREAD_C_

#ifdef WIN32
#include "thread_win32.c"
#else
#include "thread_posix.c"
#endif

#undef TAA_THREAD_C_
