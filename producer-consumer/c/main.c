#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "queue.h"

#define NUM_OF_READER_THREADS 2
#define NUM_OF_WRITER_THREADS 4

void* reader_thread(void* arg) {
  while (true) {
    uint8_t* buffer = NULL;
    uint32_t len = 0;

    // read data from the thread-safe queue.
    queue_deque(buffer, &len);
    if (buffer != NULL) {
      // process data.
      free(buffer);
    }
  }
  return NULL;
}

void* writer_thread(void* arg) {
  while (true) {
    uint32_t len = 256;
    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * len);

    // write data to the thread-safe queue.
    queue_enque(buffer, len);
  }
  return NULL;
}

int main(int argc, char** argv) {
  queue_init();

  pthread_t reader_threads[NUM_OF_READER_THREADS];
  for (int i = 0; i < NUM_OF_READER_THREADS; i++) {
    pthread_create(&reader_threads[i], NULL, reader_thread, NULL);
  }

  pthread_t writer_threads[NUM_OF_WRITER_THREADS];
  for (int i = 0; i < NUM_OF_WRITER_THREADS; i++) {
    pthread_create(&writer_threads[i], NULL, writer_thread, NULL);
  }

  return 0;
}
