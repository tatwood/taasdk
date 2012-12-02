#ifndef taa_THREAD_POSIX_H_
#define taa_THREAD_POSIX_H_

#include <pthread.h>

#define taa_THREAD_CALLCONV_TARGET

typedef intptr_t taa_thread_result_target;

typedef pthread_t taa_thread_target;

#endif // taa_THREAD_POSIX_H_
