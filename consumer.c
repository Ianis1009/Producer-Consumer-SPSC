#include <stdio.h>
#include "consumer.h"

#define LOOP 1

void *consumer_thread (void *arg) {

    ConsumerArgs *args = (ConsumerArgs*) arg;

    while (LOOP ) {
        Item item = buffer_pop(args->buffer);

        if (item.info == STOP_VALUE) {
            printf("[C]: Consumer --> Stop (-1 value identified).\n");
            break;
        }

        printf("[C]: Consumed: %d\n", item.info);
    }

    return NULL;
}