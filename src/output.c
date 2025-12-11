#include <stdio.h>

#include "../include/output.h"

int write_start(const char* filename) {
	// Open specified file in write mode
	FILE* out = fopen(filename, "w");

	// Error handling
	if (!out) {
		fprintf(stderr, "Input Error: Cannot find %s", filename);

		// Failure
		return 0;
	}

	// Output to file
	fprintf(out, "global _start\n_start:\n");
	
	// Clean up and return
	fclose(out);

	// Success
	return 1;
}

int write_exit(const char* filename, const char* num) {
	// Open specified file in write mode
	FILE* out = fopen(filename, "w");

	// Error handling
	if (!out) {
		fprintf(stderr, "Input Error: Cannot find %s", filename);

		// Failure
		return 0;
	}

	// Output to file
	fprintf(out, "    mov rax, 60\n    mov rdi, %s\n    syscall\n", num);
	
	// Clean up and return
	fclose(out);

	// Success
	return 1;
}

int write_exit_from_stack(const char* filename) {
	// Open specified file in write mode
	FILE* out = fopen(filename, "w");

	// Error handling
	if (!out) {
		fprintf(stderr, "Input Error: Cannot find %s", filename);

		// Failure
		return 0;
	}

	// Output to file
	fprintf(out, "    mov rax, 60\n    pop rdi\n    syscall\n");
	
	// Clean up and return
	fclose(out);

	// Success
	return 1;
}

int write_int(const char* filename, const char* value) {
	// Open specified file in write mode
	FILE* out = fopen(filename, "w");

	// Error handling
	if (!out) {
		fprintf(stderr, "Input Error: Cannot find %s", filename);

		// Failure
		return 0;
	}

	// Output to file
	fprintf(out, "    mov rax, %s\n    push rax\n", value);
	
	// Clean up and return
	fclose(out);

	// Success
	return 1;
}
