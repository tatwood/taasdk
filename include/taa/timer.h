#ifndef taa_TIMER_H_
#define taa_TIMER_H_

#include "system.h"

/**
 * @brief converts nanoseconds to seconds
 */
#define taa_TIMER_NS_TO_S(ns_) ((ns_)/1000000000)

/**
 * @brief converts nanoseconds to milliseconds
 */
#define taa_TIMER_NS_TO_MS(ns_) ((ns_)/1000000)

/**
 * @brief converts nanoseconds to microseconds
 */
#define taa_TIMER_NS_TO_US(ns_) ((ns_)/1000)

/**
 * @brief converts seconds to nanoseconds
 */
#define taa_TIMER_S_TO_NS(s_) ((s_) * ((int64_t) 1000000000))

/**
 * @brief converts milliseconds to nanoseconds
 */
#define taa_TIMER_MS_TO_NS(ms_) ((ms_) * ((int64_t) 1000000))

/**
 * @brief converts microseconds to nanoseconds
 */
#define taa_TIMER_US_TO_NS(us_) ((us_) * ((int64_t) 1000))

/**
 * @brief Hi precision timer, with NO guaranteed accuracy.
 * @details The results of this function can be as precise as the frequency of
 * the CPU clock, but have no guaranteed accuracy. On win32 environments, this
 * function wraps QueryPerformanceCounter, and the results can vary
 * dramatically depending on the cpu core querying the timer. Therefore, this
 * function should never be used to measure time sampled from different
 * threads. Additionally, since the same thread may switch scheduled cores in
 * some cases, dramatic forwards and backwards jumps may also be experienced
 * on a single thread. On posix environments, CLOCK_MONOTONIC is queried, and
 * is not subject to the same issues that plague win32. The results of this
 * timer should not be assumed to be compatible with the monotonic timer.
 * @return cpu timer value in nanoseconds
 */
int64_t taa_timer_sample_cpu();

/**
 * @brief Lo precision timer, with guaranteed accuracy.
 * @details The results of this function are guaranteed to be accurate, but
 * the precision may be as low as 16 ms. On win32 environments, this function
 * wraps GetTickCount. On posix environments, CLOCK_MONOTONIC is queried. The
 * results of this timer should not be assumed to be compatible with the cpu
 * timer.
 * @return monotonic timer value in nanoseconds
 */
int64_t taa_timer_sample_monotonic();

#endif // taa_TIMER_H_
