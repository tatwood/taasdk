/**
 * @brief     semaphore implementation for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by semaphore.c
#ifdef taa_SEMAPHORE_C_
#include <taa/semaphore.h>
#include <pthread.h>
#include <stdlib.h>

//****************************************************************************
int taa_semaphore_create(
    taa_semaphore* sem_out)
{
    return sem_init(sem_out, PTHREAD_PROCESS_PRIVATE, 0);
}

//****************************************************************************
int taa_semaphore_destroy(
    taa_semaphore* sem)
{
    return sem_destroy(sem);
}

//****************************************************************************
int taa_semaphore_post(
    taa_semaphore* sem)
{
    return sem_post(sem);
}

//****************************************************************************
int taa_semaphore_wait(
    taa_semaphore* sem)
{
    return sem_wait(sem);
}
#endif // taa_SEMAPHORE_C_

