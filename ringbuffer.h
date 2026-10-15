#ifndef RINGBUFFER_H

#define RINGBUFFER_H

#include <pthread.h>
#include "item.h"

#define BUFFER_CAPACITY 16

typedef struct {

    Item items[BUFFER_CAPACITY];

    int head;
    int tail;
    int count;

    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} RingBuffer;


int ringbuffer_init (RingBuffer *rb);
void ringbuffer_destroy(RingBuffer *rb);
void buffer_push(RingBuffer *rb, Item item);
Item buffer_pop (RingBuffer *rb);


#endif