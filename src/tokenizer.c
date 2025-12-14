#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "hash.h"
#include "stack.h"
#include "tokenizer.h"

Token token_create(enum TokenType type, char* value) {
	Token token;
	token.type = type;
	token.value = value;
	return token;
}

void add_token(Token token, Token** out_arr, size_t* out_size) {
	// Calculate memory that must be allocated
	size_t new_size = (*out_size + 1) * sizeof(Token);
	// Allocate more memory to Token array
	*out_arr = safe_realloc(*out_arr, new_size);
	// Add character to word array
	(*out_arr)[*out_size] = token;
	// Increment token count
	(*out_size)++;
}

Token* tokenize(char* str, size_t* out_count) {
	// Initialize token array
	Token* tokens = NULL;
	size_t token_count = 0;

	// Initialize stack
	Stack stack = stack_create(str);
	
	// Loop until peek returns null terminator
	while(peek(&stack) != '\0') {
		// Create buffer array to store words
		size_t word_cap = 16;
		char* word = safe_malloc(word_cap);
		size_t word_size = 0;
		
		// Peak current character
		char c = peek(&stack);

		// Handle multi-character tokens
		if (isalnum(c)) {
			// Loop and consume all alnum chars
			while(peek(&stack) != '\0' && isalnum(peek(&stack))) {
				// Consume char
				char curr_c = consume(&stack);

				// Only increase capacity if it would be exceeded
				if (word_size + 1 >= word_cap) {
					word_cap *= 2; // double capacity of word
					word = safe_realloc(word, word_cap);
				}

				// Add to word buffer
				word[word_size++] = curr_c;
			}

			// Ensure word is not empty
			if (word_size > 0) {
				// Shrink to exact size + null terminator
				word = safe_realloc(word, word_size + 1);
				word[word_size] = '\0';
			} else { // Safeguard just in case
				continue;
			}

			// Generate hash code
			int word_hash = gen_word_hash(word, word_size);

			// Match hash codes to tokens
			switch (word_hash) {
				case 489: // ret, shorthand alias for return
				case 783: // return
					if (strcmp(word, "return") == 0 || strcmp(word, "ret") ==0) {
						add_token(token_create(_ret, "return"), &tokens, &token_count);
					} else {
						goto handle_error;
					}
					break;
				case 459: // exit
					if (strcmp(word, "exit") == 0) {
						add_token(token_create(_exit, "exit"), &tokens, &token_count);
					} else {
						goto handle_error;
					}
					break;
				case 399: // int
					if (strcmp(word, "int") == 0) {
						add_token(token_create(_type, "int"), &tokens, &token_count);
					} else {
						goto handle_error;
					}
					break;
				default:
					goto handle_error;
			}

			free(word); // free unowned string
			continue; // skip error handling

		handle_error:
			if (isdigit(word[0])) {
				int is_valid = 1;

				// Iterate through word to ensure its all numbers
				for (size_t i = 1; i < word_size; i++) {
					if (!isdigit(word[i])) {
						is_valid = 0;
						break;
					}
				}

				if (is_valid) { // valid number
					add_token(token_create(_int, word), &tokens, &token_count);
					// word is owned by token
				} else { // mix of numbers and letters
					fprintf(stderr, "Invalid Token Error: Unknown Number %s\n", word);
					free(word);
					exit(EXIT_FAILURE);
				}
			} else {
				// Handle identifiers, ie. variable names
				add_token(token_create(_idnt, word), &tokens, &token_count);
				// word is owned by token
			}
		} 
		// Handle single-character tokens
		else {
			switch (c) {
				case '(':
					consume(&stack);
					add_token(token_create(_oparen, "("), &tokens, &token_count);
					break;
				case ')':
					consume(&stack);
					add_token(token_create(_cparen, ")"), &tokens, &token_count);
					break;
				case ';':
					consume(&stack);
					add_token(token_create(_semi, ";"), &tokens, &token_count);
					break;
				case '=':
					consume(&stack);
					add_token(token_create(_eq, "="), &tokens, &token_count);
					break;
				case ' ': 	// Space
				case '\t': 	// Horizontal Tab
				case '\n':	// Newline
				case '\r':	// Carriage Return
				case '\v':	// Vertical Tab
				case '\f':	// Form Feed
					consume(&stack);
					break;
				default: // Unrecognized character
					consume(&stack);
					fprintf(stderr, "Invalid Token Error: Unrecognized character %c\n", c);
					free(word);
					exit(EXIT_FAILURE);
			}
		}
	}

	// Add EOF token
	add_token(token_create(_eof, NULL), &tokens, &token_count);
	
	// Return count
	*out_count = token_count;

	return tokens;
}
