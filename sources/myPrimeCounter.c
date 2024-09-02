#include "../headers/my_prime_counter.h"
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

#define NUM_PRIMES (sizeof(primes) / sizeof(primes[0]))
PMyQueue queue;

void create_threads(pthread_t *threads, int *thread_data, int numberOfProcessors);
void read_numbers();
void wait_for_threads(pthread_t *threads, int *thread_data, int numberOfProcessors);
void print_total_primes(int total);

int main() {
    int numberOfProcessors = nprocs();

    if (numberOfProcessors <= 0) {
        fprintf(stderr, "Unable to determine number of processors.\n");
        return 1;
    }

    pthread_t threads[numberOfProcessors];
    int thread_data[numberOfProcessors];

    queue = createQueue();
    if (queue == NULL) {
        fprintf(stderr, "Error creating queue.\n");
        return 1;
    }

    create_threads(threads, thread_data, numberOfProcessors);
    read_numbers();
    wait_for_threads(threads, thread_data, numberOfProcessors);

    int total_counter = 0;
    for (int i = 0; i < numberOfProcessors; i++) {
        total_counter += thread_data[i];
    }

    destroyQueue(queue);
    print_total_primes(total_counter);

    return 0;
}

void create_threads(pthread_t *threads, int *thread_data, int numberOfProcessors) {
    for (int i = 0; i < numberOfProcessors; i++) {
        thread_data[i] = 0;
        int ret = pthread_create(&threads[i], NULL, &threadTask, &thread_data[i]);
        if (ret != 0) {
            fprintf(stderr, "Error creating thread.\n");
            exit(1);
        }
    }
}

void read_numbers() {
    int num;
    while (scanf("%d", &num) != EOF) {
        ADD_TO_QUEUE(queue, num);
    }

    int numberOfProcessors = nprocs();
    for (int i = 0; i < numberOfProcessors; i++) {
        ADD_TO_QUEUE(queue, -1);
    }
}

void wait_for_threads(pthread_t *threads, int *thread_data, int numberOfProcessors) {
    (void) thread_data;
    for (int i = 0; i < numberOfProcessors; i++) {
        pthread_join(threads[i], NULL);
    }
}

void print_total_primes(int total) {
    fprintf(stdout, "%d total primes.\n", total);
}

int isPrime(int n) {
    if (n <= 1) return 0;
    if (n == 2 || n == 3) return 1;

    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 0; i < (int)NUM_PRIMES; i++) {
        if (n % primes[i] == 0) return 0;
    }

    int sqrt_n = sqrt(n);
    for (int i = primes[(int)NUM_PRIMES - 1] + 2; i <= sqrt_n; i += 2) {
        if (n % i == 0) return 0;
    }

    return 1;
}

void *threadTask(void *arg) {
    int *thread_data = (int *)arg;

    while (1) {
        int task = REMOVE_FROM_QUEUE(queue);

        if (task < 0)
            break;

        *thread_data += isPrime(task);
    }

    return NULL;
}

int nprocs() {
    cpu_set_t cs;
    CPU_ZERO(&cs);
    sched_getaffinity(0, sizeof(cs), &cs);
    return CPU_COUNT(&cs);
}
