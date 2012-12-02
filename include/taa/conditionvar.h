/**
 * @brief     target agnostic condition variable header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_CONDITIONVAR_H_
#define taa_CONDITIONVAR_H_

#include "mutex.h"

#ifdef WIN32
#include "conditionvar_win32.h"
#else
#include "conditionvar_posix.h"
#endif

/**
 * @details On posix systems, this is a (pthread_cond_t); On win32, it is an
 * event (HANDLE).
 */
typedef taa_conditionvar_target taa_conditionvar;

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_conditionvar_create(
    taa_conditionvar* cvar_out);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_conditionvar_destroy(
    taa_conditionvar* cvar);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_conditionvar_signal(
    taa_conditionvar* cvar);

/**
 * @return 0 on success, -1 on error
 */
taa_SDK_LINKAGE int taa_conditionvar_wait(
    taa_conditionvar* cvar,
    taa_mutex* mtx);

#endif // taa_CONDITIONVAR_H_
