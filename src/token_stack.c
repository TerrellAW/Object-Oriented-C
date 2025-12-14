#include <string.h>

#include "../include/token_stack.h"
#include "../include/tokenizer.h"

TokenStack token_stack_create(Token* token, size_t count) {
	TokenStack stack;
	stack.idx = 0;
	stack.token = token;
	stack.count = count;
	return stack;
}

int token_peek(TokenStack* stack, Token* out_token) {
	if (stack->idx >= stack->count) {
		return 0; // Failure
	} else { 
		// Send peeked token to out pointer
		*out_token = stack->token[stack->idx];
		return 1; // Success
	}
}

int token_peekAhead(TokenStack* stack, int ahead, Token* out_token) {
	// Find index to peek to
	size_t new_idx = stack->idx + ahead;

	if (new_idx >= stack->count) {
		return 0; // Failure
	} else {
		// Send peeked token to out pointer
		*out_token = stack->token[new_idx];
		return 1; // Success
	}
}

int token_consume(TokenStack* stack, Token* out_token) {
	if (!stack->token[stack->idx].value) {
		return 0; // Failure
	}

	// Increment and send next token to out pointer
	stack->idx++; // increment stack pointer
	token_peek(stack, out_token); // update out_token
	return 1; // Success
}
