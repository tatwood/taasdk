/**
 * @brief     target agnostic coroutine implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/coroutine.h>

#define TAA_COROUTINE_C_

#ifdef WIN32
#include "coroutine_win32.c"
#else
#include "coroutine_other.c"
#endif

#undef TAA_COROUTINE_C_
