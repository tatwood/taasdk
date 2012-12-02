#ifndef taa_WORKERPOOL_H_
#define taa_WORKERPOOL_H_

#include "workqueue.h"

typedef struct taa_workerpool_s taa_workerpool;

typedef void (*taa_workerpool_startfunc)(int32_t threadindex, void* userdata);
typedef void (*taa_workerpool_stopfunc)(int32_t threadindex, void* userdata);

/**
 * @param numthreads number of worker threads to create
 * @param wq handle to the workqueue that will push jobs to the threads
 * @param wp_out out pointer to fill in with address of workerpool handle
 */
taa_SDK_LINKAGE void taa_workerpool_create(
    uint32_t numthreads,
    taa_workqueue* wq,
    taa_workerpool** wp_out);

taa_SDK_LINKAGE void taa_workerpool_destroy(
    taa_workerpool* wp);

/**
 * signals worker threads to begin processing and waits for them to initialize
 * <p>This function should only be called once, before any jobs have been
 * scheduled. It waits for the initialization function to complete on all
 * threads before returning.</p>
 * @param wp workerpool handle
 * @param startfunc optional initialization function to call on each thread
 * @param userdata optional context data to be provided to start function
 */
taa_SDK_LINKAGE void taa_workerpool_start(
    taa_workerpool* wp,
    taa_workerpool_startfunc startfunc,
    void* userdata);

/**
 * signals all worker threads to finish processing and waits for them to exit
 * @param wp workerpool handle
 * @param stopfunc optional shutdown function to call on each thread
 * @param userdata optional context data to be provided to stop function
 */
taa_SDK_LINKAGE void taa_workerpool_stop(
    taa_workerpool* wp,
    taa_workerpool_stopfunc stopfunc,
    void* userdata);

#endif // taa_WORKERPOOL_H_
