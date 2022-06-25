#ifndef array_h
#define array_h

#include "queue.h"
#include "time_mem.h"

void sd_array(int n, int interval, times_t t1,
              times_t t2, times_t t3, times_t t4);
void queuearray_push(queue_t *queue, char c_elem);
char queuearray_pop(queue_t *gueue);
void queuearray_print(queue_t *queue);

#endif /* array_h */
