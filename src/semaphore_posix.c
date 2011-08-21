/**
 * @brief     semaphore implementation for posix
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by semaphore.c
#ifdef TAA_SEMAPHORE_C_

#include <pthread.h>

//****************************************************************************
void taa_semaphore_create(
    taa_semaphore* sem)
{
    sem_init(&sem->posix, PTHREAD_PROCESS_PRIVATE, 0);
}

//****************************************************************************
void taa_semaphore_destroy(
    taa_semaphore* sem)
{
    sem_destroy(&sem->posix);
}

//****************************************************************************
void taa_semaphore_post(
    taa_semaphore* sem)
{
    sem_post(&sem->posix);
}

//****************************************************************************
void taa_semaphore_wait(
    taa_semaphore* sem)
{
    sem_wait(&sem->posix);
}

#endif // TAA_SEMAPHORE_C_
