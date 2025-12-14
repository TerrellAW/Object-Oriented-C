// Include Guard, prevents compilation errors
#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdbool.h>
#include "parser.h"

/**
 * @brief A struct for holding information about a variable.
 */
typedef struct {
	/**
	 * @brief Location in system stack that corresponds to the variable.
	 */
	size_t stack_loc;
	/**
	 * @brief Name of the variable, represents the identifier.
	 */
	const char* name;
} Var;

/**
 * @brief Code generator struct, holds necessary information for assembly code generation.
 */
typedef struct {
	/**
	 * @brief Node representing the entry point of the program.
	 */
	NodeMain root;
	/**
	 * @brief Size of the system stack.
	 */
	size_t stack_size;
	/**
	 * @brief Flag denoting whether an exit function has been called manually.
	 */
	bool has_exit; 		// Flag to track exit code
	/**
	 * @brief Array of variable structs with stack locations and names.
	 */
	Var* vars; 			// Array of variables in code
	/**
	 * @brief Tracks amount of variable structs in the array.
	 */
	size_t var_count;	// Count of variables in array
} Generator;

/**
 * @brief Constructs code generator struct.
 *
 * Constructs an empty generator struct with the given root node.
 *
 * Fields are set as follows:
 * - gen.root = root;
 * - gen.stack_size = 0;
 * - gen.has_exit = false;
 * - gen.vars = NULL;
 * - gen.var_count = 0;
 *
 * @param root The entry point node that will be used as the root of the tree.
 */
Generator gen_create(NodeMain root);

/**
 * @brief Generates assembly code from parse tree.
 *
 * Initializes a hash table of variables and uses it to add unique variable declarations
 * to the stack in assembly. Uses helper functions to generate statements and write 
 * them in assembly. Deallocates the hash table after code generation completes successfully.
 *
 * @param generator The code generator struct that will be used.
 * @param stmt_count The amount of statements that will be processed.
 * @param outputname The output file the assembly code will be written in.
 * @param out_size Out pointer to manipulate the size of the stack.
 */
int generate(Generator generator, size_t stmt_count, const char* outputname, size_t* out_size);

#endif // Closes GENERATOR_H include guard
