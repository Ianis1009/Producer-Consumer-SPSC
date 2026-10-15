#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "ringbuffer.h"
#include "producer.h"
#include "consumer.h"

#define ITEMS_TO_PRODUCE 10

int main () {


    srand(time(NULL)); // init clock

    RingBuffer buffer;
    int rb = ringbuffer_init(&buffer);

    if (rb) {
        perror("Failed to init ring buffer.\n");
        return EXIT_FAILURE;
    }

    ProducerArgs producer_args;
    producer_args.buffer = &buffer;
    producer_args.items_to_produce = ITEMS_TO_PRODUCE;

    ConsumerArgs consumer_args;
    consumer_args.buffer = &buffer;

    //producer thread
    pthread_t producer;

    //consumer thread
    pthread_t consumer;

    int rc = pthread_create(&consumer, NULL, consumer_thread, &consumer_args);

    if (rc) {
        perror("Failed to create consumer thread!\n");
        ringbuffer_destroy(&buffer);
        return EXIT_FAILURE;

    }

    int rp = pthread_create(&producer, NULL, producer_thread, &producer_args);

    if (rp) {
        perror("Failed to create producer thread.\n");
        Item stop;
        stop.info = STOP_VALUE;
        buffer_push(&buffer, stop);
        pthread_join(consumer, NULL);
        ringbuffer_destroy(&buffer);
        return EXIT_FAILURE;
    }

    pthread_join(producer, NULL);
    Item stop;
    stop.info = STOP_VALUE;
    buffer_push(&buffer, stop);
    pthread_join(consumer, NULL);

    ringbuffer_destroy(&buffer);   
    printf("[INFO]: Program finished --> Ret code: EXIT_SUCCES(0)");
    return EXIT_SUCCESS;
}