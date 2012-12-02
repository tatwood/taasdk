/**
 * @brief     futex implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by futex.c
#ifdef taa_FUTEX_C_
#include <taa/futex.h>
#include <process.h>

int taa_futex_create(
    taa_futex* ftx_out)
{
    int success = InitializeCriticalSectionAndSpinCount(ftx_out, 0x00000400);
    return (success != 0) ? 0 : -1;
}

int taa_futex_destroy(
    taa_futex* ftx)
{
    DeleteCriticalSection(ftx);
    return 0;
}

int taa_futex_lock(
    taa_futex* ftx)
{
    EnterCriticalSection(ftx);
    return 0;
}

int taa_futex_unlock(
    taa_futex* ftx)
{
    LeaveCriticalSection(ftx);
    return 0;
}

#endif // taa_FUTEX_C_
