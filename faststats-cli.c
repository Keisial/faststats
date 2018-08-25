#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/user.h>
#include "faststats.h"

int main(int argc, char **argv) {
	int index;
	int is_signed = 1;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <filename> <index> [[+|-]<value>]\n", argv[0]);
		return 1;
	}

	const int max_index = faststats_max_index();
	char *endptr;
	errno = 0;
	index = strtol(argv[2], &endptr, 10);
	if (errno || *endptr || index < 0 || index > max_index) {
		fprintf(stderr, "The index must be a number in [0, %d]\n", max_index);
		return 2;
	}

	faststats_init(argv[1]);

	if (argc < 4) {
		printf(is_signed ? "Value at %d is %lld\n" : "Value at %d is %llu\n", index, faststats_read(index));
	} else {
		const char* description;
		FASTSTATS_TYPE (*faststats_function)(int index, FASTSTATS_TYPE value);

		if (argv[3][0] == '+') {
			description = "Added";
			faststats_function = faststats_add;
			argv[3]++;
		} else if (argv[3][0] == '-') {
			description = "Substracted";
			faststats_function = faststats_sub;
			argv[3]++;
		} else {
			description = "Stored";
			faststats_function = faststats_store;
		}

		errno = 0;
		FASTSTATS_TYPE value = strtoll(argv[3], &endptr, 10);
		if (errno || *endptr) {
			fprintf(stderr, "Bad value %s\n", argv[3]);
			return 3;
		}

		FASTSTATS_TYPE new_value = faststats_function(index, value);
		printf(is_signed ? "%s %lld at %d, it is now %lld\n" : 
			"%s %llu at %d, it is now %llu\n", description, value, index, new_value);
	}

	faststats_finit();
	return 0;
}
