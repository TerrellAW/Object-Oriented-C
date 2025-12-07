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
} TokenStack;

/**
 * @brief Stack constructor.
 */
TokenStack token_stack_create(Token* token);

/**
 * @brief Peaks at next value in stack.
 */
int token_peak(TokenStack* stack, Token* out_token);

/**
 * @brief Peaks ahead the specified amount.
 */
int token_peakAhead(TokenStack* stack, int ahead, Token* out_token);

/**
 * @brief Consumes the current element and moves forward.
 */
int token_consume(TokenStack* stack, Token* out_token);

#endif // Closes TOKEN_STACK_H include guard
