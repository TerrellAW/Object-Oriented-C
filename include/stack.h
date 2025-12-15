// Include Guard, prevents compilation errors
#ifndef STACK_H
#define STACK_H

#include <string.h>

/**
 * @brief Stack data structure for characters.
 */
typedef struct {
	size_t idx;
	char* e;
} Stack;

/**
 * @brief Stack constructor.
 */
Stack stack_create(char* src);

/**
 * @brief Peeks at next value in stack.
 */
char peek(Stack* stack);

/**
 * @brief Peeks ahead the specified amount.
 */
char peekAhead(Stack* stack, int ahead);

/**
 * @brief Consumes the current element and moves forward.
 */
char consume(Stack* stack);

#endif // Closes STACK_H include guard
