#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Enumerates the valid token types for the Token struct.
 */
enum TokenType {
	_return,
	int_lit,
	semic
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

