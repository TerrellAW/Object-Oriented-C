#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#include "input.h"
#include "tokenizer.h"
#include "parser.h"
#include "generator.h"

// Long option definitions
struct option long_options[] = {
	{"asm", optional_argument, NULL, 'a'}, // --asm or -a
	{"out", required_argument, NULL, 'o'}, // --out or -o
};

int main(int argc, char* argv[]) {
	// If no launch parameters are given
	if (argc < 2) {
		// Explain usage
		fprintf(stderr, "Usage:\n");
		fprintf(stderr, "ooc <path/input.oc> [options]\n");
		fprintf(stderr, "\nThe following options are available:\n");
		fprintf(stderr, "--asm or -a : Output a human readable assembly file, can specify path/filename\n");
		fprintf(stderr, "--out or -o : Specify an output path/filename for the executable\n");

		exit(EXIT_FAILURE);
	}

	// Read input file
	long lSize = 0;
	char* code = read_input(argv[1], &lSize);
	if (!strlen(code)) {
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
		fprintf(stderr, "Parsing Error: Failed to find entry point\n");
		exit(EXIT_FAILURE);
	}

	// Create generator
	Generator gen = gen_create(prog);

	// Get chosen options
	bool asm_flag = false;
	char asm_out[128] = {0};
	bool out_flag = false;
	char out[64];
	int opt;
	while ((opt = getopt_long(argc, argv, "ao:", long_options, NULL)) != -1) {
		switch (opt) {
			case 'a':
				asm_flag = true;
				if (optarg != NULL) {
					sprintf(asm_out, "%s", optarg);
				}
				break;
			case 'o':
				sprintf(out, "%s", optarg);
				out_flag = true;
				break;
		}
	}

	// TODO: Separate output for obj and bin

	// Set output name
	if (!out_flag) {
		// Get name without path
		const char* full_path = argv[1];
		const char* file_strt = full_path;

		// Find last forward slash
		char* slash = strrchr(full_path, '/');
		if (slash != NULL) {
			file_strt = slash + 1; // Start after slash
		}

		// Get name of file without extension
		char* dot = strrchr(full_path, '.');

		if (dot != NULL) {
			// Calculate length before dot
			size_t len = dot - file_strt;
			// Ensure out buffer is large enough
			if (len < 64) {
				strncpy(out, file_strt, len);
				out[len] = '\0';
			} else {
				fprintf(stderr, "Output Error: Path too long\n");
				exit(EXIT_FAILURE);
			}
		} else {
			// No dot found
			fprintf(stderr, "Input Error: Incorrect file format\n");
		}
	}
	char asmf[255];
	if (asm_out[0] != '\0') {
		// User provided path
		sprintf(asmf, "%s", asm_out);
	} else {
		sprintf(asmf, "%s.asm", out);
	}
	char nasmf[272];
	sprintf(nasmf, "nasm -felf64 %s", asmf);
	char ldf[255];
	sprintf(ldf, "ld -o %s %s.o", out, out);

	// Generate assembly
	generate(gen, stmt_count, asmf, &gen.stack_size);

	// Call nasm
	system(nasmf);
	// Call linker
	system(ldf);

	// Delete asm file by default
	char rmasm[272];
	sprintf(rmasm, "rm %s", asmf);
	if (!asm_flag) {
		system(rmasm);
	}

	// Clean and exit
	free(code);
	exit(EXIT_SUCCESS);
}
