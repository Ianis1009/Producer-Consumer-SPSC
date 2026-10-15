# Producer-Consumer-SPSC

SPSC - Simple Producer Simple Consumer

**Producer-Consumer problem** in C using POSIX threads (`pthreads`).  A producer generates items and places them into a shared bounded buffer, while a consumer retrieves and processes them.

## Threads

The program uses two threads:
- **Producer thread** - generates a fixed number of items and inserts them into the buffer.
- **Consumer thread** - removes items from the buffer and processes them.

## Ring Buffer 

The ring buffer is a used as a FIFO queue. It reuses array positions by wrapping around when the end is reached.

- `head` - position from which the next item is consumed.
- `tail` - position where the next item is produced.
- `count` - number of items currently stored. 

When the buffer is full, the producer waits. When it is empty, the consumer waits. This prevents inserting into a full buffer or removing from an empty one.

## Synchronization

- **Mutex (`pthread_mutex_t`)** protects the buffer while it is being accessed.
- **Condition variables (`not_full`, `not_empty`)** allow threads to wait until the buffer is ready for an operation.
- **`STOP_VALUE`** is a special item used to notify the consumer that production has finished.

Condition variables are checked in `while` loops to ensure the buffer state is valid before an operation continues.

## Technologies

- C
- POSIX Threads (`pthreads`)
- Mutexes and condition variables
- Circular buffers
- GNU Make

## Build and Run

Compile:

```bash
make
```

Run the program:
```bash
make run
```

