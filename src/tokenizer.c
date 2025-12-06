#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/tokenizer.h"

Token* tokenize(const char* str) {
	// Get element count
	size_t count = strlen(str);
	
	// Loop through elements
	for (size_t i = 0; i < count; i++) {
		char c = str[i];
		printf("%c", c);
	}

	return NULL;
}
