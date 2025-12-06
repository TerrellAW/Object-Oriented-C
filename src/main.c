#include <stdlib.h>
#include <stdio.h>

#include "../include/input.h"
#include "../include/tokenizer.h"

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
	Token* tokens = tokenize(code);

	// Clean and exit
	free(code);
	exit(EXIT_SUCCESS);
}
