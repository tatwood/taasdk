/**
 * @brief     target agnostic condition variable implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#define taa_CONDITIONVAR_C_

#ifdef WIN32
#include "conditionvar_win32.c"
#else
#include "conditionvar_posix.c"
#endif

#undef taa_CONDITIONVAR_C_
