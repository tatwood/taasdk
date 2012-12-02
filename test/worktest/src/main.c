#if defined(_DEBUG) && defined(_MSC_FULL_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <taa/workqueue.h>
#include <taa/workerpool.h>
#include <taa/thread.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMTHREADS 16
#define NUMLOOPS 100

typedef struct testdata_s testdata;

struct testdata_s
{
    int startthreadindex;
    taa_thread_id threadid;
    int value;
};

void teststart(int threadindex, void* userdata)
{
    testdata* td = ((testdata*) userdata) + threadindex;
    td->startthreadindex = threadindex;
    td->threadid = taa_thread_self();
    td->value = 1;
}

void testjob(void* userdata)
{
    testdata* td = (testdata*) userdata;
    // try to vary the time each job takes to execute
    taa_sleep(rand() % 100);
    td->threadid = taa_thread_self();
    ++td->value;
}

int main(int argc, char* argv[])
{
    testdata data[NUMTHREADS];
    int results[NUMTHREADS];
    taa_workqueue* wq;
    taa_workerpool* wp;
    int i;
    memset(results, 0, sizeof(results));
    memset(data, 0, sizeof(data));
    // intentionally attempt to force overflow of job capacity
    taa_workqueue_create(NUMTHREADS/2, &wq);
    taa_workerpool_create(NUMTHREADS, wq, &wp);
    taa_workerpool_start(wp, teststart, data);
    i = 0;
    while(1)
    {
        int j;
        int total = 0;
        for(j = 0; j < NUMTHREADS; ++j)
        {
            int startthread = data[j].startthreadindex;
            int v = data[j].value;
            // each data index should be initialized by the thread at that
            // index. After the data is initialized, any thread may modify
            // it, depending on the which thread consumes the job, but
            // only one job is scheduled for each data index at a time,
            // and values should only be incrementing in steps of 1
            if(startthread != j)
            {
                assert(0);
            }
            if(results[j] != v)
            {
                taa_thread_id id = data[j].threadid;
                assert(v == results[j]+1);
                results[j] = v;
                printf("data %2i set to %3i by thread %08x\n", j, v, (int) id);
                if(i != NUMLOOPS*NUMTHREADS)
                {
                    // if the maximum number of jobs has not been scheduled,
                    // schedule a new one.
                    taa_workqueue_push(wq, testjob, data+j);
                    ++i;
                }
            }
            total += results[j];
        }
        if(total == (NUMLOOPS+1)*NUMTHREADS)
        {
            // the final total should be:
            // 1*NUMTHREADS for the start function +
            // NUMLOOPS*NUMTHREADS for the scheduled jobs
            break;
        }
        taa_sched_yield();
    }
    taa_workerpool_stop(wp, NULL, NULL);
    taa_workerpool_destroy(wp);
    taa_workqueue_destroy(wq);
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
