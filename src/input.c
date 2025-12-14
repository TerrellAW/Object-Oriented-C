#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

char* read_input(const char* filename, long* file_size) {
	// Open specified file in binary read mode
	FILE* in = fopen(filename, "rb");

	// Error handling
	if (!in) {
		fprintf(stderr, "Input Error: Cannot find %s", filename);

		// Failure
		return NULL;
	}

	// Find file size
	fseek(in, 0L, SEEK_END); // Send cursor to end of file
	long lSize = ftell(in); // Get size from cursor position
	rewind(in); // Send cursor back to beginning of file
	
	// Allocate memory for file
	char* buffer = safe_calloc(1, lSize + 1); // Allocate for content and null terminator
	if (!buffer) {
		fclose(in);
		fprintf(stderr, "Input Error: Failed to allocate memory for %s", filename);

		// Failure
		return NULL;
	}

	// Verify memory size
	long result = fread(buffer, 1, lSize, in); // Read lSize elements
	if (result != lSize) {
		fclose(in);
		free(buffer);
		fprintf(stderr, "Input Error: Failed to read %s", filename);

		// Failure
		return NULL;
	}

	// Clean up and return
	fclose(in);
	if (file_size != NULL) {
		*file_size = lSize; // Pass size back to caller
	}

	return buffer;
}
