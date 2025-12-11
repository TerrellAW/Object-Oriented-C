// Include Guard, prevents compilation errors
#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include "parser.h"

typedef struct {
	NodeMain root;
} Generator;

/**
 * @brief Constructs generator.
 */
Generator gen_create(NodeMain root);

/**
 * @brief Generates assembly code from parse tree.
 */
int generate(Generator generator, size_t stmt_count, const char* outputname);

#endif // Closes GENERATOR_H include guard
