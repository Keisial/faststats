#include <sys/types.h>
#include <sys/user.h>
#include <sys/shm.h>
#include <stddef.h>
#include <fcntl.h>

#include "faststats.h"

static STATS_TYPE *memory_block = NULL;

int faststats_init(const char* filename) {
	void *memory;
	key_t key = ftok(filename, 'S');
	if (key == -1) {
		return -1;
	}

	int shmid = shmget(key, PAGE_SIZE, IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	
	memory = shmat(shmid, NULL, 0);
	if (memory == (void*)-1) {
		return -1;
	}
	memory_block = memory;
	
	return 0;
}

int faststats_finit() {
	return shmdt(memory_block);
}

int __attribute__((const)) faststats_max_index(void) {
	return (PAGE_SIZE -1) / sizeof(STATS_TYPE);
}

STATS_TYPE faststats_read(int index) {
	return __atomic_load_n(&memory_block[index], __ATOMIC_SEQ_CST);
}

STATS_TYPE faststats_store(int index, STATS_TYPE value) {
	__atomic_store_n(&memory_block[index], value, __ATOMIC_SEQ_CST);
	return value;
}

STATS_TYPE faststats_add(int index, STATS_TYPE value) {
	return __atomic_add_fetch(&memory_block[index], value, __ATOMIC_SEQ_CST);
}

STATS_TYPE faststats_sub(int index, STATS_TYPE value) {
	return __atomic_sub_fetch(&memory_block[index], value, __ATOMIC_SEQ_CST);
}
