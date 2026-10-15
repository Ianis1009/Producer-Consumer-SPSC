#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer.h"


#define BUFFER_EMPTY 0

int ringbuffer_init (RingBuffer *rb) {

    rb ->head = 0;
    rb ->tail = 0;
    rb ->count = 0;

    int r = pthread_mutex_init(&rb->mutex, NULL);

    if (r) {
        printf("Error: Mutex init failed...\n");
        return EXIT_FAILURE;
    }

    r = pthread_cond_init(&rb ->not_empty, NULL);

    if (r) {
        pthread_mutex_destroy(&rb->mutex);
        return EXIT_FAILURE;
    }

    r =  pthread_cond_init(&rb->not_full, NULL);
    if (r) {
        pthread_cond_destroy(&rb->not_empty);
        pthread_mutex_destroy(&rb->mutex);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void ringbuffer_destroy (RingBuffer *rb) {

    pthread_cond_destroy(&rb->not_empty);
    pthread_cond_destroy(&rb->not_full);
    pthread_mutex_destroy(&rb->mutex);
}

void buffer_push (RingBuffer *rb, Item item) {

    pthread_mutex_lock(&rb->mutex);

    while (rb ->count == BUFFER_CAPACITY) {
        pthread_cond_wait(&rb->not_full, &rb->mutex);
    } //while buffer is full

    rb ->items[rb ->tail] = item;
    rb ->tail = (rb ->tail + 1) % BUFFER_CAPACITY;
    rb ->count++;

    pthread_cond_signal(&rb->not_empty);
    pthread_mutex_unlock(&rb->mutex);

}

Item buffer_pop (RingBuffer *rb) {

    pthread_mutex_lock(&rb ->mutex);

    while (rb ->count == BUFFER_EMPTY) {
        pthread_cond_wait(&rb->not_empty, &rb->mutex);
    }

    Item item = rb ->items[rb->head];
    rb ->head = (rb->head + 1) % BUFFER_CAPACITY;
    rb ->count --;

    pthread_cond_signal(&rb->not_full);
    pthread_mutex_unlock(&rb->mutex);
    
    return item;
}