#include <string.h>

#include "stack.h"

Stack stack_create(char* src) {
	Stack stack;
	stack.idx = 0;
	stack.e = src;
	return stack;
}

char peek(Stack* stack) {
	if (stack->e[stack->idx] == '\0') { // check if at end of string
		return '\0'; // return null terminator
	} else {
		return stack->e[stack->idx]; // return element
	}
}

char peekAhead(Stack* stack, int ahead) {
	// Find index to peek to
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
