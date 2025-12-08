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

int token_peak(TokenStack* stack, Token* out_token) {
	if (stack->idx >= stack->count) {
		return 0; // Failure
	} else { 
		// Send peaked token to out pointer
		*out_token = stack->token[stack->idx];
		return 1; // Success
	}
}

int token_peakAhead(TokenStack* stack, int ahead, Token* out_token) {
	// Find index to peak to
	size_t new_idx = stack->idx + ahead;

	if (new_idx >= stack->count) {
		return 0; // Failure
	} else {
		// Send peaked token to out pointer
		*out_token = stack->token[new_idx];
		return 1; // Success
	}
}

int token_consume(TokenStack* stack, Token* out_token) {
	if (!stack->token[stack->idx].value) {
		return 0; // Failure
	}

	// Send current token to out pointer and then increment
	*out_token = stack->token[stack->idx++]; // postfix increment
	return 1; // Success
}
