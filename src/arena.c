#include <stdio.h>
#include <stdlib.h>

#include "arena.h"
#include "utils.h"

ArenaAllocator arena_create(size_t alloc_size) {
	ArenaAllocator arena;
	arena.buffer = safe_malloc(alloc_size);
	arena.offset = arena.buffer;
	return arena;
}

char* alloc(ArenaAllocator* arena, size_t offset_size) {
	char* offset = arena->offset;
	arena->offset += offset_size;
	return offset;
}

void arena_free(ArenaAllocator* arena) {
	free(arena->buffer);
}
