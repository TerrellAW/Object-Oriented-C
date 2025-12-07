#include <stdlib.h>
#include <stdio.h>

#include "../include/input.h"
#include "../include/output.h"
#include "../include/tokenizer.h"

// Temp, until parser is implemented
void tokens_to_asm(const Token* tokens, size_t count) {

	for (size_t i = 0; i < count; i++) {
		const Token token = tokens[i];

		if (token.type == _ret) {
			if (i + 2 < count) {
				const Token num = tokens[i + 1];
				const Token semi = tokens[i + 2];
				
				if (num.type == _int && semi.type == _semi) {
					write_asm("out.asm", num.value);
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {
	// If no launch parameters are given
	if (argc < 2) { // TODO: Add arg for asm file output
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

	// Output assembly to out.asm
	tokens_to_asm(tokens, 3);

	// Call nasm
	system("nasm -felf64 out.asm");
	// Call linker
	system("ld -o out out.o");

	// Clean and exit
	free(code);
	exit(EXIT_SUCCESS);
}
