/**
 * @brief     target agnostic semaphore implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/semaphore.h>

#define TAA_SEMAPHORE_C_

#ifdef WIN32
#include "semaphore_win32.c"
#else
#include "semaphore_posix.c"
#endif

#undef TAA_SEMAPHORE_C_
