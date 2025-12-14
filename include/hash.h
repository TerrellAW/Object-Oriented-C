// Include Guard, prevents compilation errors
#ifndef HASH_H
#define HASH_H

#include <stdlib.h>

/**
 * @brief Generates a simple hash code for a word.
 *
 * Uses a simple formula to convert a string into an integer using
 * the string's length, the ASCII code of its first character
 * and the ASCII code of its last character.
 * The formula is:
 * length * 100 + (word[0] - 'a') * 10 + (word[length - 1] - 'a')
 *
 * @param word String of characters to hash into an integer.
 * @param length Size of the string, used in hashing calculation.
 *
 * @return Hash code for the given string, or 0 if length is 0.
 */
int gen_word_hash(const char* word, size_t length);

#endif // Closes HASH_H include guard
