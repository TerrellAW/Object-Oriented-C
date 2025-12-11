#include <stdio.h>

/**
 * @brief Write assembly code to start the program.
 */
int write_start(const char* filename);

/**
 * @brief Writes assembly code to exit the program.
 */
int write_exit(const char* filename, const char* val);

/**
 * @brief Writes exit assembly with exit code from the stack.
 */
int write_exit_from_stack(const char* filename);

/**
 * @brief Pushes an integer variable onto the system stack.
 */
int write_int(const char* filename, const char* value);
