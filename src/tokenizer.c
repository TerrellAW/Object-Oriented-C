#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/utils.h"
#include "../include/hash.h"
#include "../include/stack.h"
#include "../include/tokenizer.h"

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

Token* tokenize(char* str) {
	// Initialize token array
	Token* tokens = NULL;
	size_t token_count = 0;

	// Initialize stack
	Stack stack = stack_create(str);
	
	// Loop until peak returns null terminator
	while(peak(&stack) != '\0') {
		// Create buffer array to store words
		char* word = NULL;
		size_t word_size = 0;
		
		// Peak current character
		char c = peak(&stack);

		// Handle multi-character tokens
		if (isalnum(c)) {
			// Loop and consume all alnum chars
			while(peak(&stack) != '\0' && isalnum(peak(&stack))) {
				// Consume char
				char curr_c = consume(&stack);

				// Add to word buffer
				size_t new_size = (word_size + 1) * sizeof(char);
				word = safe_realloc(word, new_size);
				word[word_size++] = curr_c;
			}

			// Terminate the word string
			if (word_size > 0) {
				word = safe_realloc(word, word_size + 1);
				word[word_size] = '\0';
			} else {
				continue; // just in case
			}

			// Generate hash code
			int word_hash = gen_word_hash(word, word_size);

			// Match hash codes to tokens
			switch (word_hash) {
				case 783: // return
					if (strcmp(word, "return") == 0) {
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
				default:
					goto handle_error;
			}

			free(word); // free unowned string
			continue; // skip error handling

		handle_error:
			if (isdigit(word[0])) {
				add_token(token_create(_int, word), &tokens, &token_count);
				// word is owned by token
			} else {
				// TODO: Handle identifiers, ie. variable names
				fprintf(stderr, "Invalid Token Error: Unknown Identifier/Number %s", word);
				free(word);
				exit(EXIT_FAILURE);
			}
		} 
		// Handle single-character tokens
		else {
			switch (c) {
				case ';':
					consume(&stack);
					add_token(token_create(_semi, ";"), &tokens, &token_count);
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
					fprintf(stderr, "Invalid Token Error: Unrecognized character %c", c);
					free(word);
					exit(EXIT_FAILURE);
			}
		}
	}

	// TODO: EOF token if needed
	
	return tokens;
}
