#include <stdlib.h>
#include <stdio.h>

#include "../include/input.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"
#include "../include/generator.h"

int main(int argc, char* argv[]) {
	// If no launch parameters are given
	if (argc < 2) { // TODO: Add arg for asm file output
		// Explain usage
		fprintf(stderr, "Usage:\n");
		fprintf(stderr, "ooc <input.oc>");

		exit(EXIT_FAILURE);
	}

	// TODO: Add arg for executable name
	
	// Read input file
	long lSize = 0;
	char* code = read_input(argv[1], &lSize);
	if (!code) {
		exit(EXIT_FAILURE);
	}

	// Tokenize code string
	size_t token_count = 0;
	Token* tokens = tokenize(code, &token_count);

	// Create parser
	Parser parser = parser_create(tokens, token_count);

	// Parse tokens
	size_t stmt_count = 0;
	NodeMain prog = parse(parser, &stmt_count);

	// Parse failure
	if (!prog.stmts) {
		fprintf(stderr, "Parsing Error: Failed to find entry point.");
		exit(EXIT_FAILURE);
	}

	// Create generator
	Generator gen = gen_create(prog);

	// Generate assembly
	generate(gen, stmt_count, "out.asm", &gen.stack_size); // TODO: Get output filename from user input or source file name

	// Call nasm
	system("nasm -felf64 out.asm"); // TODO: File name from user input or source file name
	// Call linker
	system("ld -o out out.o"); // TODO: File name from user input or source file name

	// Clean and exit
	free(code);
	exit(EXIT_SUCCESS);
}
