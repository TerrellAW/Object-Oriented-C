#include <stdio.h>

/**
 * @brief Write assembly code to start the program.
 *
 * Should be used at the start of an assembly program.
 * Outputs these assembly instructions:
 * @code
 * global _start	; sets _start as the program's entry point
 * _start:			; start of the program
 * @endcode
 *
 * @param filename The path of the file to write assembly to.
 * @return 1 if the write succeeded, 0 if it failed.
 */
int write_start(const char* filename);

/**
 * @brief Writes assembly code to exit the program.
 *
 * Should be used at the end of the assembly program.
 * Outputs these assembly instructions:
 * @code
 *     mov rax, 60	; loads the exit() syscall
 *	   mov rdi, val ; passes given value to exit(val)
 *	   syscall		; executes exit(val),
 *	   				; exits program and returns val as exit code
 * @endcode
 *
 * @param filename The path of the file to write assembly to.
 * @param val The exit code for the program, must be an integer of 0-255.
 *
 * @return 1 if the write succeeded, 0 if it failed.
 */
int write_exit(const char* filename, const char* val);

/**
 * @brief Writes exit assembly with exit code from the stack.
 *
 * For use with manual exit calls in the code being compiled.
 * Uses the write_pop() function to pop the value at the stack 
 * pointer into rdi where it will be used as the exit code.
 * Outputs these assembly instructions:
 * @code
 *     mov rax, 60	; loads the exit() syscall
 *	   pop rdi		; pop value at stack pointer into exit(rdi)
 *	   syscall		; executes exit(rdi),
 *	   				; exits program and returns value from rdi as exit code
 * @endcode
 *
 * @param filename The path of the file to write assembly to.
 * @param out_size Out pointer to track the size of the stack.
 *
 * @return 1 if the write succeeded, 0 if it failed.
 */
int write_exit_from_stack(const char* filename, size_t* out_size);

/**
 * @brief Pushes the given value or register onto the system stack.
 *
 * Can be used to handle variables in assembly.
 * The variable will be associated with the position of its value
 * on the system stack.
 * Outputs this assembly instruction:
 * @code
 *     push reg		; pushes the value at reg onto the stack
 * @endcode
 *
 * @param filename The path of the file to write assembly to.
 * @param reg A register or value to push onto the stack, 
 * 		      must be an integer 0-255 or a valid x86 CPU register.
 * @param out_size Out pointer to track the size of the stack.
 *
 * @return 1 if the write succeeded, 0 if it failed.
 */
int write_push(const char* filename, const char* reg, size_t* out_size);

/**
 * @brief Pops a value from the system stack into the given register.
 *
 * Used to take a value from the stack so it can be used.
 * Outputs this assembly instruction:
 * @code
 *     pop reg		; pops the value at the stack pointer into reg
 * @endcode
 *
 * @param filename The path of the file to write assembly to.
 * @param reg A register to pop the value into, must be a valid x86 CPU register.
 * @param out_size Out pointer to track the size of the stack.
 *
 * @return 1 if the write succeeded, 0 if it failed.
 */
int write_pop(const char* filename, const char* reg, size_t* out_size);
