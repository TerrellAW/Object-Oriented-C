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
	
	// Loop through alphanumeric elements
	for (size_t i = 0; i < count; i++) {
		// Create buffer array to store words
		char* word = NULL;
		size_t word_size = 0;

		char c = str[i];
		int has_run = 0;
		while (isalnum(c)) {
			add_char(&c, &word, &word_size);
			add_num(&c, &word, &word_size);
			i++;
			c = str[i];
			has_run = 1;
		}

		// Add null terminator if word has content
		if (word_size > 0 && word != NULL) {
			word = safe_realloc(word, word_size + 1);
			word[word_size] = '\0';
		}

		// Check if index needs to decrement
		if (has_run == 1) {
			i--;
			c = str[i];
		}

		// Check if string matches token
		if (word && strcmp(word, "return") == 0) {
			Token token = token_create(_ret, "return");
			add_token(token, &tokens, &token_count);
			free(word);
			continue;
		} else if (word && isdigit(word[0])) { // TODO: Loop to verify whole word isdigit
			Token token = token_create(_int, word);
			add_token(token, &tokens, &token_count);
		} else if (c == ';') {
			Token token = token_create(_semi, ";");
			add_token(token, &tokens, &token_count);
		} else if (isspace(c)) {
			continue;
		} else {
			fprintf(stderr, "Invalid Token Error: %s", word);
			free(word);
			exit(EXIT_FAILURE);
		}
	}
	return tokens;
}
