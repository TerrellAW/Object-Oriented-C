// Include Guard, prevents compilation errors
#ifndef GENERATOR_H
#define GENERATOR_H

#include "parser.h"
#include <stdio.h>

typedef struct {
	NodeExit root; // Temporary root
} Generator;

/**
 * @brief Constructs generator.
 */
Generator gen_create(NodeExit root);

/**
 * @brief Generates assembly code from parse tree.
 */
int generate(Generator generator, size_t count);

#endif // Closes GENERATOR_H include guard
