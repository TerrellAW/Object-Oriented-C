#include <stdlib.h>

int gen_word_hash(const char* word, size_t length) {
	if (length == 0) {
		return 0;
	}

	// Generate hash based on length, first character and last character
	return (int)length * 100 + (word[0] - 'a') * 10 + (word[length - 1] - 'a');
}
