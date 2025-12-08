#include <stdio.h>

#include "../include/generator.h"
#include "../include/output.h"
#include "../include/parser.h"

Generator gen_create(NodeExit root) {
	Generator gen;
	gen.root = root;
	return gen;
}

int generate(Generator generator, size_t count) {
	return write_asm("out.asm", generator.root.expr.token.value); // TODO: Take file name from user input
}
