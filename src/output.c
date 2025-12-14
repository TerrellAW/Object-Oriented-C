#include <stdio.h>

#include "output.h"

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
	// Open specified file in append mode
	FILE* out = fopen(filename, "a");

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

int write_exit_from_stack(const char* filename, size_t* out_size) {
	// Open specified file in append mode
	FILE* out = fopen(filename, "a");

	// Error handling
	if (!out) {
		fprintf(stderr, "Input Error: Cannot find %s", filename);

		// Failure
		return 0;
	}

	// Output to file
	fprintf(out, "    mov rax, 60\n"); // load exit() syscall
	write_pop(filename, "rdi", out_size);
	fprintf(out, "    syscall\n"); // execute
	
	// Clean up and return
	fclose(out);

	// Success
	return 1;
}

int write_push(const char* filename, const char* reg, size_t* out_size) {
	// Open specified file in append mode
	FILE* out = fopen(filename, "a");

	// Error handling
	if (!out) {
		fprintf(stderr, "Input Error: Cannot find %s", filename);

		// Failure
		return 0;
	}

	// Output to file
	fprintf(out, "    push %s\n", reg);

	// Increment size of stack
	(*out_size)++;
	
	// Clean up and return
	fclose(out);

	// Success
	return 1;
}

int write_pop(const char* filename, const char* reg, size_t* out_size) {
	// Open specified file in append mode
	FILE* out = fopen(filename, "a");

	// Error handling
	if (!out) {
		fprintf(stderr, "Input Error: Cannot find %s", filename);

		// Failure
		return 0;
	}

	// Output to file
	fprintf(out, "    pop %s\n", reg);

	// Increment size of stack
	(*out_size)--;
	
	// Clean up and return
	fclose(out);

	// Success
	return 1;
}
