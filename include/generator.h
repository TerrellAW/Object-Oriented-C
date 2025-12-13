// Include Guard, prevents compilation errors
#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdbool.h>
#include "parser.h"

typedef struct {
	NodeMain root;
	size_t stack_size;
	bool has_exit; // Flag to track exit code
} Generator;

/**
 * @brief Constructs generator.
 */
Generator gen_create(NodeMain root);

/**
 * @brief Generates assembly code from parse tree.
 */
int generate(Generator generator, size_t stmt_count, const char* outputname, size_t* out_size);

#endif // Closes GENERATOR_H include guard
