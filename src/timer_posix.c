/**
 * @brief     timer implementation for posix target
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by timer.c
#ifdef taa_TIMER_C_

#include <taa/timer.h>
#include <time.h>

//****************************************************************************
int64_t taa_timer_sample_cpu()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((int64_t) ts.tv_sec)*1000000000L + ts.tv_nsec;
}

//****************************************************************************
int64_t taa_timer_sample_monotonic()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((int64_t) ts.tv_sec)*1000000000L + ts.tv_nsec;
}

#endif // taa_TIMER_C_
