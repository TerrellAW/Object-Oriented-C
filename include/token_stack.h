// Include Guard, prevents compilation errors
#ifndef TOKEN_STACK_H
#define TOKEN_STACK_H

#include <string.h>

#include "tokenizer.h"

/**
 * @brief Stack data structure for tokens.
 */
typedef struct {
	size_t idx;
	Token* token;
	size_t count;
} TokenStack;

/**
 * @brief Stack constructor.
 */
TokenStack token_stack_create(Token* token, size_t count);

/**
 * @brief Peeks at next value in stack.
 */
int token_peek(TokenStack* stack, Token* out_token);

/**
 * @brief Peeks ahead the specified amount.
 */
int token_peekAhead(TokenStack* stack, int ahead, Token* out_token);

/**
 * @brief Consumes the current element and moves forward.
 */
int token_consume(TokenStack* stack, Token* out_token);

#endif // Closes TOKEN_STACK_H include guard
