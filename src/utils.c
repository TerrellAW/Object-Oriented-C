#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

// Memory allocation wrapper
void* safe_malloc(size_t size) {
	void* mptr = malloc(size);
	if (!mptr) {
		fprintf(stderr, "Allocation Error: safe_malloc failed to allocate %zu bytes\n", size);
		exit(EXIT_FAILURE);
	}

	return mptr;
}

// Zero-initialized memory allocation wrapper
void* safe_calloc(size_t num, size_t size) {
	void* cptr = calloc(num, size);
	if (!cptr || !num) {
		fprintf(stderr, "Allocation Error: safe_calloc failed to allocate %zu bytes for %zu elements\n", size, num);
		exit(EXIT_FAILURE);
	}

	return cptr;
}

// Memory reallocation wrapper
void* safe_realloc(void* ptr, size_t size) {
	void* rptr = realloc(ptr, size);
	if (!rptr) {
		fprintf(stderr, "Allocation Error: safe_realloc failed to reallocate %zu bytes\n", size);
		exit(EXIT_FAILURE);
	}

	return rptr;
}

// Copy a string
char* safe_strdup(const char* s) {
	size_t slen = strlen(s);
	char* res = safe_malloc(slen + 1);
	if (res == NULL) {
		return NULL; // handle alloc failure, probably unecessary
	}
	memcpy(res, s, slen + 1); // copy data into new, bigger string
	return res; // return result
}
