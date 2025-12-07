#include <string.h>

#include "../include/stack.h"

Stack stack_create(char* src) {
	Stack stack;
	stack.idx = 0;
	stack.e = src;
	return stack;
}

const char peak(Stack* stack) {
	if (stack->e[stack->idx] == '\0') { // check if at end of string
		return '\0'; // return null terminator
	} else {
		return stack->e[stack->idx]; // return element
	}
}

const char peakAhead(Stack* stack, int ahead) {
	// Find index to peak to
	size_t new_idx = stack->idx + ahead;

	if (stack->e[new_idx] == '\0') {
		return '\0';
	} else {
		return stack->e[new_idx];
	}
}

char consume(Stack* stack) {
	if (stack->e[stack->idx] == '\0') {
		return '\0';
	}

	// Return current char and then increment
	return stack->e[stack->idx++]; // postfix increment
}
