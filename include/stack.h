// Include Guard, prevents compilation errors
#ifndef STACK_H
#define STACK_H

#include <string.h>

/**
 * @brief Stack data structure for characters.
 */
typedef struct {
	int idx;
	char* e;
} Stack;

/**
 * @brief Stack constructor.
 */
Stack stack_create(char* src);

/**
 * @brief Peaks at next value in stack.
 */
const char peak(Stack* stack);

/**
 * @brief Peaks ahead the specified amount.
 */
const char peakAhead(Stack* stack, int ahead);

/**
 * @brief Consumes the current element and moves forward.
 */
char consume(Stack* stack);

#endif // Closes STACK_H include guard
