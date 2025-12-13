// Include Guard, prevents compilation errors
#ifndef UTILS_H
#define UTILS_H

// Standard Library
#include <stdio.h>

/**
 * @brief Allocates memory safely.
 *
 * Wraps malloc() and exits the program if allocation fails, such as when size is 0.
 *
 * @param size Number of bytes to allocate. Must be a valid positive integer.
 * @return Pointer to allocated memory.
 */
void* safe_malloc(size_t size);

/**
 * @brief Safely allocates memory with all bytes initialized to zero.
 *
 * Wraps calloc() and exits the program if allocation fails, such as when size is 0.
 *
 * @param size Size in bytes of each element. Must be a valid positive integer.
 * @param num Number of elements to be allocated. Must be a valid positive integer.
 * @return Pointer to allocated memory.
 */
void* safe_calloc(size_t num, size_t size);

/**
 * @brief Reallocates memory safely.
 *
 * Wraps realloc() and exits the program if reallocation fails, such as when size is 0.
 *
 * @param ptr Pointer to memory that needs to be reallocated.
 * @param size Number of bytes to allocate. Must be a valid positive integer.
 * @return Pointer to allocated memory.
 */
void* safe_realloc(void* ptr, size_t size);

/**
 * @brief Copies a string.
 *
 * Custom implementation of POSIX strdup().
 * Allocates memory using safe_malloc(), which handles allocation failures.
 *
 * @param s String of characters to copy.
 * @return Pointer to first character of duplicate string.
 */
char* safe_strdup(const char* s);

#endif // Closes UTILS_H include guard
