#include <stdint.h>

#ifndef FASTSTATS_TYPE
#define FASTSTATS_TYPE uint64_t
#endif

int faststats_init(const char* filename);
int faststats_finit(void);
int __attribute__((const)) faststats_max_index(void);

FASTSTATS_TYPE faststats_read(int index);
FASTSTATS_TYPE faststats_store(int index, FASTSTATS_TYPE value);
FASTSTATS_TYPE faststats_add(int index, FASTSTATS_TYPE value);
FASTSTATS_TYPE faststats_sub(int index, FASTSTATS_TYPE value);
