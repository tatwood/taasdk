/**
 * @brief     timer implementation for win32 target
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by timer.c
#ifdef taa_TIMER_C_

#include <taa/timer.h>

//****************************************************************************
int64_t taa_timer_sample_cpu()
{
    static double s_freq;
    LARGE_INTEGER qword;
    QueryPerformanceCounter(&qword);
    if(s_freq == 0.0)
    {
        LARGE_INTEGER qword;
        QueryPerformanceFrequency(&qword);
        s_freq = 1000000000.0/qword.QuadPart;
    }
    return (int64_t) (qword.QuadPart * s_freq);
}

//****************************************************************************
int64_t taa_timer_sample_monotonic()
{
    // GetTickCount is measured in 32 bits and overflows every 50 days
    // these static variables handle the rollover
    static uint64_t s_inittime = 0;
    static uint64_t s_rollover = 0;
    uint64_t ticks = GetTickCount() + s_rollover;
    if(s_inittime == 0)
    {
        s_inittime = ticks;
    }
    if(ticks < s_inittime)
    {
        // NOTE: this is not thread safe
        // compensate for 32 bit overflow
        ticks += 0xffffffff;
        s_inittime += 0xffffffff;
        s_rollover += 0xffffffff;
    }
    return ticks * 1000000; // convert from ms to ns
}

#endif // taa_TIMER_C_
