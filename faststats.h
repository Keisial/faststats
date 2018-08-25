#include <stdint.h>

#ifndef STATS_TYPE
#define STATS_TYPE uint64_t
#endif

int faststats_init(const char* filename);
int faststats_finit(void);
int __attribute__((const)) faststats_max_index(void);

STATS_TYPE faststats_read(int index);
STATS_TYPE faststats_store(int index, STATS_TYPE value);
STATS_TYPE faststats_add(int index, STATS_TYPE value);
STATS_TYPE faststats_sub(int index, STATS_TYPE value);
