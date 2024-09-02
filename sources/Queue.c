#include "../headers/Queue.h"
#include <stdio.h>
#include <stdlib.h>

PMyQueue createQueue() {
    PMyQueue queue = (PMyQueue)malloc(sizeof(MyQueue));
    if (!queue) {
        return NULL;
    }

    queue->head = 0;
    queue->tail = -1;
    queue->count = 0;

    if (INIT_MUTEX(&queue->mutex) != 0) {
        free(queue);
        return NULL;
    }

    if (INIT_COND(&queue->canAdd) != 0) {
        DESTROY_MUTEX(&queue->mutex);
        free(queue);
        return NULL;
    }

    if (INIT_COND(&queue->canRemove) != 0) {
        DESTROY_MUTEX(&queue->mutex);
        DESTROY_COND(&queue->canAdd);
        free(queue);
        return NULL;
    }

    return queue;
}

void destroyQueue(PMyQueue queue) {
    if (queue == NULL) {
        return;
    }

    LOCK_MUTEX(&queue->mutex);

    DESTROY_MUTEX(&queue->mutex);
    DESTROY_COND(&queue->canAdd);
    DESTROY_COND(&queue->canRemove);

    free(queue);
}

void enqueue(PMyQueue queue, int value) {
    if (!queue) {
        return;
    }

    LOCK_MUTEX(&queue->mutex);

    while (queue->count == QUEUE_CAPACITY) {
        WAIT_COND(&queue->canAdd, &queue->mutex);
    }

    queue->tail = (queue->tail + 1) % QUEUE_CAPACITY;
    queue->elements[queue->tail] = value;
    queue->count++;

    SIGNAL_COND(&queue->canRemove);
    UNLOCK_MUTEX(&queue->mutex);
}

int dequeue(PMyQueue myqueue) {
    if (!myqueue ) {
        return -1;
    }

    LOCK_MUTEX(&myqueue->mutex);

    while (myqueue->count == 0) {
        WAIT_COND(&myqueue->canRemove, &myqueue->mutex);
    }

    int value = myqueue->elements[myqueue->head];
    myqueue->head = (myqueue->head + 1) % QUEUE_CAPACITY;
    myqueue->count--;

    SIGNAL_COND(&myqueue->canAdd);
    UNLOCK_MUTEX(&myqueue->mutex);

    return value;
}

int isQueueEmpty(PMyQueue myqueue) {
    if (!myqueue) {
        return -1;
    }

    LOCK_MUTEX(&myqueue->mutex);
    int isEmpty = (myqueue->count == 0);
    UNLOCK_MUTEX(&myqueue->mutex);

    return isEmpty;
}
