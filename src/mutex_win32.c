/**
 * @brief     mutex implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by mutex.c
#ifdef taa_MUTEX_C_
#include <taa/mutex.h>
#include <process.h>

int taa_mutex_create(
    taa_mutex* mtx_out)
{
    HANDLE h = CreateMutex(NULL, FALSE, NULL);
    *mtx_out = h;
    return (h != NULL) ? 0 : -1;
}

int taa_mutex_destroy(
    taa_mutex* mtx)
{
    return (CloseHandle(*mtx) != 0) ? 0 : -1;
}

int taa_mutex_lock(
    taa_mutex* mtx)
{
    return (WaitForSingleObject(*mtx, INFINITE) != WAIT_FAILED) ? 0 : -1;
}

int taa_mutex_unlock(
    taa_mutex* mtx)
{
    return (ReleaseMutex(*mtx) != 0) ? 0 : -1;
}

#endif // taa_MUTEX_C_
