// Include Guard, prevents compilation errors
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Enumerates the valid token types for the Token struct.
 */
enum TokenType {
	_ret, 	// return
	_int, 	// int
	_semi 	// ;
};

/**
 * @brief Data structure for storing Token information after tokenization.
 */
typedef struct {
	enum TokenType type;
	char* value;
} Token;

/**
 * @brief Turns a string into a collection of tokens.
 */
Token* tokenize(const char* str);

#endif // Closes TOKENIZER_H include guard
