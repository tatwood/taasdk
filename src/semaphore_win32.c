/**
 * @brief     semaphore implementation for win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by semaphore.c
#ifdef TAA_SEMAPHORE_C_

//****************************************************************************
void taa_semaphore_create(
    taa_semaphore* sem)
{
    sem->win32 = CreateSemaphore(NULL, 0, 0x7FFFFFFF, NULL);
}

//****************************************************************************
void taa_semaphore_destroy(
    taa_semaphore* sem)
{
    CloseHandle(sem->win32);
}

//****************************************************************************
void taa_semaphore_post(
    taa_semaphore* sem)
{
    ReleaseSemaphore(sem->win32, 1, NULL);
}

//****************************************************************************
void taa_semaphore_wait(
    taa_semaphore* sem)
{
    WaitForSingleObject(sem->win32, INFINITE);
}

#endif // TAA_SEMAPHORE_C_
