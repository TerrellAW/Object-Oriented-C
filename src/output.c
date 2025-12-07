#include <stdio.h>

int write_asm(const char* filename) {
	// Open specified file in write mode
	FILE* out = fopen(filename, "w");

	// Error handling
	if (!out) {
		fprintf(stderr, "Input Error: Cannot find %s", filename);

		// Failure
		return 1;
	}

	
	
	// Clean up and return
	fclose(out);

	// Success
	return 0;
}
