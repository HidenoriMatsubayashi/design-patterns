#include "queue.h"

#include <pthread.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 10

typedef struct QueueBuffer {
  uint8_t* buffer;
  uint32_t len;
} QueueBuffer;

static QueueBuffer s_buffer[MAX_QUEUE_SIZE];
static int s_head = 0;
static int s_tail = 0;

static pthread_mutex_t s_mutex;
static pthread_cond_t s_full;
static pthread_cond_t s_empty;

static bool is_full() { return s_head == (s_tail + 1) % MAX_QUEUE_SIZE; }

static bool is_empty() { return s_head == s_tail; }

void queue_init() {
  pthread_mutex_init(&s_mutex, NULL);
  pthread_cond_init(&s_full, NULL);
  pthread_cond_init(&s_empty, NULL);
}

void queue_enque(uint8_t* buffer, uint32_t len) {
  pthread_mutex_lock(&s_mutex);

  while (is_full()) {
    pthread_cond_wait(&s_full, &s_mutex);
  }

  QueueBuffer data = {.buffer = buffer, .len = len};
  s_buffer[s_tail] = data;
  s_tail = (s_tail + 1) % MAX_QUEUE_SIZE;

  pthread_cond_signal(&s_empty);
  pthread_mutex_unlock(&s_mutex);
}

void queue_deque(uint8_t* buffer, uint32_t* len) {
  pthread_mutex_lock(&s_mutex);

  while (is_empty()) {
    pthread_cond_wait(&s_empty, &s_mutex);
  }

  QueueBuffer data = s_buffer[s_head];
  buffer = data.buffer;
  *len = data.len;
  s_head = (s_head + 1) % MAX_QUEUE_SIZE;

  pthread_cond_signal(&s_full);
  pthread_mutex_unlock(&s_mutex);
}
