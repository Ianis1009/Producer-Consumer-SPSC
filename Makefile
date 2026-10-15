
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -pthread
TARGET = producer_consumer

SOURCES = main.c ringbuffer.c producer.c consumer.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c item.h ringbuffer.h producer.h consumer.h
ringbuffer.o: ringbuffer.c ringbuffer.h item.h
producer.o: producer.c producer.h ringbuffer.h item.h
consumer.o: consumer.c consumer.h ringbuffer.h item.h

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)
