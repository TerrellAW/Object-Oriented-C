#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/utils.h"
#include "../include/tokenizer.h"

void add_char(char* out_c, char** out_arr, size_t* out_size) {
	// Look for alphabetical chars
	if (isalpha(*out_c)) {
		// Calculate memory that must be allocated
		size_t new_size = (*out_size + 1) * sizeof(char);
		// Allocate more memory for the word array
		*out_arr = safe_realloc(*out_arr, new_size);
		// Add character to word array
		(*out_arr)[*out_size] = *out_c;
		// Increment word_size
		(*out_size)++;
	}
}

void add_num(char* out_c, char** out_arr, size_t* out_size) {
	// Look for alphabetical chars
	if (isdigit(*out_c)) {
		// Calculate memory that must be allocated
		size_t new_size = (*out_size + 1) * sizeof(char);
		// Allocate more memory for the word array
		*out_arr = safe_realloc(*out_arr, new_size);
		// Add character to word array
		(*out_arr)[*out_size] = *out_c;
		// Increment word_size
		(*out_size)++;
	}
}

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

Token* tokenize(const char* str) {
	// Initialize token array
	Token* tokens = NULL;
	size_t token_count = 0;
	
	// Get element count
	size_t count = strlen(str);
	
	// Create buffer array to store words
	char* word = NULL;
	size_t word_size = 0;

	// Loop through alphanumeric elements
	for (size_t i = 0; i < count; i++) {
		char c = str[i];
		while (isalnum(c)) {
			add_char(&c, &word, &word_size);
			add_num(&c, &word, &word_size);
			i++;
			c = str[i];
		}

		// Check if string matches token
		if (strcmp(word, "return") == 0) {
			Token token = token_create(_ret, "return");
			add_token(token, &tokens, &token_count);
			free(word);
		} else if (isdigit(word[0])) {
			Token token = token_create(_int, word);
			add_token(token, &tokens, &token_count);
			free(word);
		} else if (c == ';') {
			Token token = token_create(_semi, ";");
			add_token(token, &tokens, &token_count);
		} else if (isspace(str[i - 1])) {
			continue;
		} else {
			fprintf(stderr, "Invalid Token Error: %s", word);
			free(word);
			exit(EXIT_FAILURE);
		}
	}
	return tokens;
}
