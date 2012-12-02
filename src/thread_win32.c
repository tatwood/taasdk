/**
 * @brief     thread management implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by thread.c
#ifdef taa_THREAD_C_
#include <taa/thread.h>
#include <process.h>

//****************************************************************************
int taa_thread_create(
    taa_thread_func func,
    void* args,
    taa_thread* t_out)
{
    HANDLE h = (HANDLE) _beginthreadex(
        NULL,
        0,
        func,
        args,
        0,
        NULL);
    *t_out = h;
    return (h != NULL) ? 0 : -1;
}

//****************************************************************************
int taa_thread_equal(
    taa_thread_id a,
    taa_thread_id b)
{
    return a == b;
}

//****************************************************************************
taa_thread_result taa_thread_join(
    taa_thread t)
{
    DWORD ret;
    WaitForSingleObject((HANDLE) t, INFINITE);
    GetExitCodeThread((HANDLE) t, &ret);
    CloseHandle((HANDLE) t);
    return (taa_thread_result) ret;
}

//****************************************************************************
taa_thread_id taa_thread_self()
{
    return (taa_thread_id) GetCurrentThreadId();
}

#endif // taa_THREAD_C_
