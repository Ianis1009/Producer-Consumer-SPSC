#ifndef PRODUCER_H
#define PRODUCER_H


#include "ringbuffer.h"

typedef struct {
    RingBuffer *buffer;
    int items_to_produce;
} ProducerArgs;

Item generate_item (void);
void *producer_thread (void *arg);


#endif