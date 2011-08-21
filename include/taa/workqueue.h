/**
 * @brief     an asychronous work scheduler header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_WORKQUEUE_H_
#define TAA_WORKQUEUE_H_

#include "render.h"

typedef int32_t (*taa_workqueue_func)(void* userdata);
typedef void (*taa_workqueue_callback)(int32_t result, void* userdata);

/**
 * an asychronous work scheduling system with callback notifications
 */
typedef struct taa_workqueue_s taa_workqueue;

taa_EXTERN_C void taa_workqueue_create(
    taa_window_display* windisp,
    taa_rendercontext* rc,
    uint32_t capacity,
    taa_workqueue** wqout);

taa_EXTERN_C void taa_workqueue_destroy(
    taa_workqueue* wq);

/**
 * <p>This function is implemented with the assumption that work will only be
 * pushed by one thread per queue instance. The thread resonsible for pushing
 * work to a queue must regularly call update on that queue. Callbacks
 * will be executed on the same thread that is pushing the work.</p>
 */
taa_EXTERN_C void taa_workqueue_push(
    taa_workqueue* wq,
    taa_workqueue_func workfunc,
    taa_workqueue_callback callback,
    void* userdata);

/**
 * <p>The thread resonsible for pushing work to a queue must regularly call
 * this function to update that queue. This function will execute any pending
 * callback notifications for completed work.</p>
 */
taa_EXTERN_C void taa_workqueue_update(
    taa_workqueue* wq);

#endif // TAA_WORKQUEUE_H_
