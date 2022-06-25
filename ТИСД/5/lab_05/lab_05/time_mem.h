#ifndef timemem_h
#define timemem_h

#include "queue.h"
#include "array.h"
#include "list.h"

double getime(times_t t);

int64_t tick(void);

void check_memory_time(void);

#endif /* timemem_h */
