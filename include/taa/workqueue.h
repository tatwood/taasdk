/**
 * @brief     an asychronous work scheduler header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_WORKQUEUE_H_
#define taa_WORKQUEUE_H_

#include "system.h"

typedef struct taa_workqueue_s taa_workqueue;

typedef void (*taa_workqueue_func)(void* userdata);

//****************************************************************************

taa_SDK_LINKAGE void taa_workqueue_abort(
    taa_workqueue* wq);

/**
 * @param capacity maximum number of jobs that can be queued at a time
 * @param wq_out out pointer to fill in with address of workqueue handle
 */
taa_SDK_LINKAGE void taa_workqueue_create(
    uint32_t capacity,
    taa_workqueue** wq_out);

taa_SDK_LINKAGE void taa_workqueue_destroy(
    taa_workqueue* wq);

taa_SDK_LINKAGE int32_t taa_workqueue_pop(
    taa_workqueue* wq,
    int32_t block,
    taa_workqueue_func* func_out,
    void** data_out);

taa_SDK_LINKAGE void taa_workqueue_push(
    taa_workqueue* wq,
    taa_workqueue_func func,
    void* userdata);

#endif // taa_WORKQUEUE_H_
