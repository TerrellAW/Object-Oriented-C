#include <stdio.h>

int write_asm(const char* filename, const char* num) {
	// Open specified file in write mode
	FILE* out = fopen(filename, "w");

	// Error handling
	if (!out) {
		fprintf(stderr, "Input Error: Cannot find %s", filename);

		// Failure
		return 1;
	}

	// Output to file
	fprintf(out, "global _start\n_start:\n    mov rax, 60\n    mov rdi, %s\n    syscall\n", num);
	
	// Clean up and return
	fclose(out);

	// Success
	return 0;
}
