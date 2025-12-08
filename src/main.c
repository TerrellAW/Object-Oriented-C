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
		fprintf(stderr, "ooc <input.ooc>");

		exit(EXIT_FAILURE);
	}

	// TODO: Read config file for project name, etc...
	
	// Read input file
	long lSize = 0;
	char* code = read_input(argv[1], &lSize);
	if (!code) {
		exit(EXIT_FAILURE);
	}

	// Tokenize code string
	Token* tokens = tokenize(code);

	// Create parser
	Parser parser = parser_create(tokens);

	// Parse tokens
	NodeExit ext = parse(parser);

	// Create generator
	Generator gen = gen_create(ext);

	// Generate assembly
	generate(gen, 3); // TODO: Take count from tokenizer or parser

	// Call nasm
	system("nasm -felf64 out.asm"); // TODO: File name from user input
	// Call linker
	system("ld -o out out.o"); // TODO: File name from user input

	// Clean and exit
	free(code);
	exit(EXIT_SUCCESS);
}
