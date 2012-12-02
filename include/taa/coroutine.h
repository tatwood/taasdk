/**
 * @brief     target agnostic coroutine header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_COROUTINE_H_
#define taa_COROUTINE_H_

#include "system.h"

#ifdef WIN32
#include "coroutine_win32.h"
#else
#include "coroutine_other.h"
#endif

typedef void (*taa_coroutine_func)(void* args);

/**
 * @details On win32, this is a fiber (HANDLE), on other operating systems,
 * this is an abstract pointer.
 */
typedef taa_coroutine_target taa_coroutine;

taa_SDK_LINKAGE int taa_coroutine_create(
    size_t stacksize,
    taa_coroutine_func func,
    void* userdata,
    taa_coroutine* co_out);

taa_SDK_LINKAGE int taa_coroutine_destroy(
    taa_coroutine co);

/**
 * @brief begin execution of a coroutine
 * @details Immediately switches the context of the current thread to the
 * specified coroutine. Unlike win32 fibers, which terminate the thread once
 * the coroutine exits, this implementation will return to the original
 * context and continue normal thread execution. The coroutine may be executed
 * again after it terminates.
 */
taa_SDK_LINKAGE int taa_coroutine_execute(
    taa_coroutine co);

/**
 * @brief switch context from one coroutine to another
 * @details Immediately switches the context of the current coroutine to the
 * specified coroutine. This function can only be called from within another
 * coroutine. When it, the active coroutine is suspended until the newly
 * activated coroutine returns or a switch is performed back to the previous
 * context. Whe the context becomes active again, execution continues where it
 * left off.
 */
taa_SDK_LINKAGE void taa_coroutine_switch(
    taa_coroutine co);

#endif // taa_COROUTINE_H_
