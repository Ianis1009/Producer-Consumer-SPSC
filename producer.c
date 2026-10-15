#include <stdio.h>
#include <stdlib.h>
#include "producer.h"

Item generate_item () {

    Item item;
    int random_value = (rand () % 10) * (rand() % 1000) + rand() % 3;
    item.info = random_value;

    return item;
}

void *producer_thread (void *arg) {

    ProducerArgs *args = (ProducerArgs *)arg;

    for (int i = 0; i < args ->items_to_produce; i++ ) {
        Item item = generate_item();
        printf("[P]: Producer --> %d\n", item.info);
        buffer_push(args->buffer, item);
    }

    printf("[INFO]: Producer --> Finished...\n");

    return NULL; 
}