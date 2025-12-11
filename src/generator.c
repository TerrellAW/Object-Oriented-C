#include <stdio.h>
#include <stdbool.h>

#include "../include/generator.h"
#include "../include/output.h"
#include "../include/parser.h"

Generator gen_create(NodeMain root) {
	Generator gen;
	gen.root = root;
	gen.has_exit = false;
	return gen;
}

void gen_expr(const NodeExpr expr, const char* outputname) {
	switch (expr.type) {
		case expr_int:
			write_int(outputname, expr.token.value); // Push value of integer onto stack
			break;
		case expr_idnt:
			exit(EXIT_FAILURE); // TODO
		default:
			exit(EXIT_FAILURE); // TODO
	}
}

void gen_stmt(Generator* generator, const NodeStmt stmt, const char* outputname) {
	switch (stmt.type) {
		case stmt_exit:
			gen_expr(stmt.expr, outputname); // Push variable onto stack
			write_exit_from_stack(outputname); // Pop value from stack for exit code
			generator->has_exit = true;
			break;
		case stmt_ret:
			// TODO: Have return not exit, but return
			gen_expr(stmt.expr, outputname);
			write_exit_from_stack(outputname);
			generator->has_exit = true;
			break;
		case stmt_type:
			exit(EXIT_FAILURE); // TODO
		default:
			exit(EXIT_FAILURE); // TODO
	}
}

int generate(Generator generator, size_t stmt_count, const char* outputname) {
	// Start program
	write_start(outputname);

	// Loop through statements
	for (size_t i = 0; i < stmt_count; i++) {
		gen_stmt(&generator, generator.root.stmts[i], outputname);
	}

	// End program if not already ended
	if (!generator.has_exit) {
		write_exit(outputname, "0"); // default status code, 0 for successful program execution
	}
	return 1; // successful function execution
}
