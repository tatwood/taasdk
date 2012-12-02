/**
 * @brief     condition variable implementation for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by conditionvar.c
#ifdef taa_CONDITIONVAR_C_
#include <taa/conditionvar.h>

int taa_conditionvar_create(
    taa_conditionvar* cvar_out)
{
    return pthread_cond_init(cvar_out, NULL);
}

int taa_conditionvar_destroy(
    taa_conditionvar* cvar)
{
    return pthread_cond_destroy(cvar);
}

int taa_conditionvar_signal(
    taa_conditionvar* cvar)
{
    return pthread_cond_signal(cvar);
}

int taa_conditionvar_wait(
    taa_conditionvar* cvar,
    taa_mutex* mtx)
{
    return pthread_cond_wait(cvar, mtx);
}

#endif // taa_CONDITIONVAR_C_
