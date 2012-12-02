#if defined(_DEBUG) && defined(_MSC_FULL_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "cfutex.h"
#include <taa/futex.h>
#include <taa/mutex.h>
#include <taa/spinlock.h>
#include <taa/thread.h>
#include <taa/timer.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef NDEBUG
#error asserts are not enabled
#endif

#define NUMTHREADS 64
#define NUMLOOPS 100

enum
{
    MODE_MUTEX,
    MODE_FUTEX,
    MODE_CFUTEX,
    MODE_SPIN,
    NUM_MODES
};

typedef struct thread_data_s thread_data;

struct thread_data_s
{
    taa_thread thread;
    uint64_t waittime;
    unsigned counter;
};

static int mode;
static int quit;
static unsigned counter;

static taa_mutex s_mutex;
static taa_futex s_futex;
static cfutex s_cfutex;
static unsigned s_spinlock;

thread_data data[NUMTHREADS];

//****************************************************************************
static taa_thread_result taa_THREAD_CALLCONV thread_func(
    void* args)
{
    thread_data* data = (thread_data*) args;
    while(!quit)
    {
        int i;
        int j;
        float f;
        int64_t t0;
        int64_t t1;
        t0 = taa_timer_sample_cpu();
        switch(mode)
        {
        case MODE_MUTEX: taa_mutex_lock(&s_mutex); break;
        case MODE_FUTEX: taa_futex_lock(&s_futex); break;
        case MODE_CFUTEX: cfutex_lock(&s_cfutex); break;
        case MODE_SPIN : taa_SPINLOCK_LOCK(&s_spinlock); break;
        }
        t1 = taa_timer_sample_cpu();
        i= counter;
        data->waittime += t1 - t0;
        f = 0.0f;
        for(j = 0; j < 100; ++j)
        {
            f += 0.00025f * j;
        }
        ++data->counter;
        // increments counter by 1
        assert(((int) f) == 1);
        counter = i + ((int) f);
        switch(mode)
        {
        case MODE_MUTEX: taa_mutex_unlock(&s_mutex); break;
        case MODE_FUTEX: taa_futex_unlock(&s_futex); break;
        case MODE_CFUTEX: cfutex_unlock(&s_cfutex); break;
        case MODE_SPIN : taa_SPINLOCK_UNLOCK(&s_spinlock); break;
        }
        taa_sched_yield();
    }
    return 0;
}

int main(int argc, char* argv[])
{
    int i;
    int total;
    quit = 0;
    taa_mutex_create(&s_mutex);
    taa_futex_create(&s_futex);
    cfutex_create(&s_cfutex);
    s_spinlock = 0;
    for(mode = 0; mode < NUM_MODES; ++mode)
    {
        quit = 0;
        counter = 0;
        total = 0;
        for(i = 0; i < NUMTHREADS; ++i)
        {
            data[i].waittime = 0;
            data[i].counter = 0;
            taa_thread_create(thread_func, data + i, &data[i].thread);
        }
        taa_sleep(10 * 1000);
        quit = 1;
        printf("***********************************************\n");
        switch(mode)
        {
        case MODE_MUTEX : printf("native mutex results\n"); break;
        case MODE_FUTEX : printf("native futex results\n"); break;
        case MODE_CFUTEX: printf("custom futex results\n"); break;
        case MODE_SPIN  : printf("spinlock results\n"); break;
        }
        for(i = 0; i < NUMTHREADS; ++i)
        {
            double ms;
            taa_thread_join(data[i].thread);
            ms = taa_TIMER_NS_TO_MS((double) data[i].waittime);
            printf(
                "thread %2i count: %7i, locked time: %8.3f\n",
                i,
                data[i].counter,
                ms);
            total += data[i].counter;
        }
        assert(total == counter);
        printf("total count %u\n", total);
    }
    taa_mutex_destroy(&s_mutex);
    taa_futex_destroy(&s_futex);
    cfutex_destroy(&s_cfutex);
#if defined(_DEBUG) && defined(_MSC_FULL_VER)
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtCheckMemory();
    _CrtDumpMemoryLeaks();
#endif
    return EXIT_SUCCESS;
}
