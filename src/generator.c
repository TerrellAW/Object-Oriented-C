#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../include/generator.h"
#include "../include/output.h"
#include "../include/parser.h"
#include "../include/var_hsh_map.h"
#include "utils.h"

ht map; // init empty map

Generator gen_create(NodeMain root) {
	Generator gen;
	gen.root = root;
	gen.stack_size = 0;
	gen.has_exit = false;
	gen.vars = NULL;
	gen.var_count = 0;
	return gen;
}

void gen_expr(const NodeExpr expr, const char* outputname, size_t* out_size) {
	switch (expr.type) {
		case expr_int:
			write_push(outputname, expr.token.value, out_size); // Push value of integer onto stack
			break;
		case expr_idnt:
			exit(EXIT_FAILURE); // TODO actually deal with identifiers
		default:
			exit(EXIT_FAILURE); // TODO error handling
	}
}

void gen_stmt(Generator* generator, const NodeStmt stmt, const char* outputname, size_t* out_size) {
	switch (stmt.type) {
		case stmt_exit:
			gen_expr(stmt.expr, outputname, out_size); // Push variable onto stack
			write_exit_from_stack(outputname, out_size); // Pop value from stack for exit code
			generator->has_exit = true;
			break;
		case stmt_ret:
			// TODO: Have return not exit, but return
			gen_expr(stmt.expr, outputname, out_size);
			write_exit_from_stack(outputname, out_size);
			generator->has_exit = true;
			break;
		case stmt_type:
			for (size_t i = 0; i < generator->var_count; i++) {
				if (strcmp(stmt.var.node_type.idnt.value, generator->vars[i].name)) {
					fprintf(stderr, "Compiler Error: Identifier already used %s\n", generator->vars[i].name);
					exit(EXIT_FAILURE);
				}

				// Add to generator
				Var var; // Initialize variable struct
				var.name = stmt.var.node_type.idnt.value; // Get name from identifier
				var.stack_loc = *out_size; // Top of stack is size of stack
			    size_t new_size = generator->var_count + 1;
				generator->vars = safe_realloc(generator->vars, new_size); // Allocate space for new var
				generator->vars[generator->var_count] = var; // Add new var to generator
				generator->var_count++; // Increment count

				// Insert variable into map
				ht_insert(&map, generator->vars[generator->var_count - 1].name,
						&generator->vars[generator->var_count - 1].name);
				
				// Evaluate expression
				gen_expr(stmt.expr, outputname, out_size); // Push expression onto stack

				// TODO: Push into system stack
				
			}
		default:
			exit(EXIT_FAILURE); // TODO error handling
	}
}

int generate(Generator generator, size_t stmt_count, const char* outputname, size_t* out_size) {
	// Start program
	write_start(outputname);

	// Loop through statements
	for (size_t i = 0; i < stmt_count; i++) {
		gen_stmt(&generator, generator.root.stmts[i], outputname, out_size);
	}

	// End program if not already ended
	if (!generator.has_exit) {
		write_exit(outputname, "0"); // default status code, 0 for successful program execution
	}
	return 1; // successful function execution
}

