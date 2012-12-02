/**
 * @brief     semaphore implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by semaphore.c
#ifdef taa_SEMAPHORE_C_
#include <taa/semaphore.h>

//****************************************************************************
int taa_semaphore_create(
    taa_semaphore* sem_out)
{
    HANDLE h = CreateSemaphore(NULL, 0, 0x7FFFFFFF, NULL);
    *sem_out = h;
    return (h != NULL) ? 0 : -1;
}

//****************************************************************************
int taa_semaphore_destroy(
    taa_semaphore* sem)
{
    return (CloseHandle(*sem) != 0) ? 0 : -1;
}

//****************************************************************************
int taa_semaphore_post(
    taa_semaphore* sem)
{
    return (ReleaseSemaphore(*sem, 1, NULL) != 0) ? 0 : -1;
}

//****************************************************************************
int taa_semaphore_wait(
    taa_semaphore* sem)
{
    return (WaitForSingleObject(*sem, INFINITE) != WAIT_FAILED) ? 0 : -1;
}

#endif // taa_SEMAPHORE_C_
