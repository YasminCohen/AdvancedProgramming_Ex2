#ifndef _MY_QUEUE_H
#define _MY_QUEUE_H

#include <pthread.h>

#define QUEUE_CAPACITY 100000

typedef struct {
    int elements[QUEUE_CAPACITY];
    int head;
    int tail;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t canAdd;
    pthread_cond_t canRemove;
} MyQueue, *PMyQueue;

PMyQueue createQueue();
void destroyQueue(PMyQueue queue);
void enqueue(PMyQueue queue, int value);
int dequeue(PMyQueue queue);
int isQueueEmpty(PMyQueue queue);

#define ADD_TO_QUEUE(queue, value) enqueue(queue, value)
#define REMOVE_FROM_QUEUE(queue) dequeue(queue)
#define INIT_MUTEX(mutex) pthread_mutex_init(mutex, NULL)
#define LOCK_MUTEX(mutex) pthread_mutex_lock(mutex)
#define UNLOCK_MUTEX(mutex) pthread_mutex_unlock(mutex)
#define DESTROY_MUTEX(mutex) pthread_mutex_destroy(mutex)
#define INIT_COND(cond) pthread_cond_init(cond, NULL)
#define WAIT_COND(cond, mutex) pthread_cond_wait(cond, mutex)
#define SIGNAL_COND(cond) pthread_cond_signal(cond)
#define DESTROY_COND(cond) pthread_cond_destroy(cond)

#endif 
