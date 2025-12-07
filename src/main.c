#include <stdlib.h>
#include <stdio.h>

#include "../include/input.h"
#include "../include/tokenizer.h"

// Temp, until parser is implemented
void tokens_to_asm(const Token* tokens, size_t count) {

	for (size_t i = 0; i < count; i++) {
		const Token token = tokens[i];
		const char* num = tokens[i + 1].value;

		if (token.type == _ret) {
			if (i++ < count && tokens[i + 1].type == _int) {
				if (i + 2 < count && tokens[i + 2].type == _semi) {
					printf("global _start\nstart:\n    mov rax, 60\n    mov rdi, %s\n    syscall", num);
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {
	// If no launch parameters are given
	if (argc != 2) {
		// Explain usage
		fprintf(stderr, "Usage:\n");
		fprintf(stderr, "ooc <input.ooc>");

		exit(EXIT_FAILURE);
	}
	
	// Read input file
	long lSize = 0;
	char* code = read_input(argv[1], &lSize);
	if (!code) {
		exit(EXIT_FAILURE);
	}

	// Tokenize code string
	const Token* tokens = tokenize(code);

	// Calculate size of array
	size_t arrlen = sizeof(*tokens);
	size_t tokens_len = arrlen / sizeof(tokens[0]);

	// Output assembly to terminal
	tokens_to_asm(tokens, tokens_len);

	// Clean and exit
	free(code);
	exit(EXIT_SUCCESS);
}
