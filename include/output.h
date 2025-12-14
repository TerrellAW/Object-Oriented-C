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
int write_exit_from_stack(const char* filename, size_t* out_size);

/**
 * @brief Pushes the given value or register (reg) onto the system stack.
 */
int write_push(const char* filename, const char* reg, size_t* out_size);

/**
 * @brief Pops a value from the system stack into a register.
 */
int write_pop(const char* filename, const char* reg, size_t* out_size);
