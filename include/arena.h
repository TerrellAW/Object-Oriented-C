// Include Guard, prevents compilation errors
#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>

/**
 * @brief Struct for arena allocator.
 */
typedef struct {
	char* buffer;
	char* offset;
} ArenaAllocator;

/**
 * @brief Construct an arena allocator struct.
 */
ArenaAllocator arena_create(size_t alloc_size);

/**
 * @brief Frees memory associated with arena allocator.
 */
void arena_free(ArenaAllocator* arena);

#endif // Closes ARENA_H include guard
