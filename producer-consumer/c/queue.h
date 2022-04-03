#include <stdint.h>
#include <stdio.h>

extern void queue_init();
extern void queue_enque(uint8_t* buffer, uint32_t len);
extern void queue_deque(uint8_t* buffer, uint32_t* len);
