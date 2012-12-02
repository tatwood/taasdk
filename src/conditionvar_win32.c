/**
 * @brief     condition variable implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by conditionvar.c
#ifdef taa_CONDITIONVAR_C_
#include <taa/conditionvar.h>
#include <process.h>

int taa_conditionvar_create(
    taa_conditionvar* cvar_out)
{
    HANDLE h = CreateEvent(NULL, FALSE, FALSE, NULL);
    *cvar_out = h;
    return (h != NULL) ? 0 : -1;
}

int taa_conditionvar_destroy(
    taa_conditionvar* cvar)
{
    return (CloseHandle(*cvar) != 0) ? 0 : -1;
}

int taa_conditionvar_signal(
    taa_conditionvar* cvar)
{
    return (SetEvent(*cvar) != 0) ? 0 : -1;
}

int taa_conditionvar_wait(
    taa_conditionvar* cvar,
    taa_mutex* mtx)
{
    int err = -1;
    HANDLE hcvar = *cvar;
    HANDLE hmtx = *mtx;
    // ResetEvent attempts to mimic phtreads behavior
    // (if not waiting when signalled, signal is lost)
    if(ResetEvent(hcvar) != 0)
    {
        // theoretically, the thread signalling should have the mutex locked
        // during the signal and the thread waiting should have locked the
        // mutex before entering wait, so there should not be a race condition
        //  here.

        // release mutex and wait for event
        if(SignalObjectAndWait(hmtx, hcvar, INFINITE, FALSE) != WAIT_FAILED)
        {
            // relock the mutex
            if(WaitForSingleObject(hmtx, INFINITE) != WAIT_FAILED)
            {
                err = 0;
            }
        }
    }
    return err;    
}

#endif // taa_CONDITIONVAR_C_

