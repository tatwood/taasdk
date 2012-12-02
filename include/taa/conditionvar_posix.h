/**
 * @brief     condition variable header for posix target
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_CONDITIONVAR_POSIX_H_
#define taa_CONDITIONVAR_POSIX_H_

#include <pthread.h>

typedef pthread_cond_t taa_conditionvar_target;

#endif // taa_CONDITIONVAR_POSIX_H_
