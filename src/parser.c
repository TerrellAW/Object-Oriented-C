#include <stdio.h>

#include "../include/parser.h"
#include "../include/tokenizer.h"
#include "../include/token_stack.h"
#include "../include/utils.h"

Parser parser_create(Token* tokens, size_t count) {
	Parser parser;
	parser.tokens = tokens;
	parser.count = count;
	return parser;
}

ExprType set_expr_type(Token token) {
	if (token.type) {
		switch (token.type) {
			case _int:
				return expr_int;
			case _idnt:
				return expr_idnt;
			default:
				// If token does not have a valid type, should be impossible
				fprintf(stderr, "Parsing Error: Unexpected token %s\n", token.value);
				exit(EXIT_FAILURE);
		}
	}

	// If token does not have a valid type, should be impossible
	fprintf(stderr, "Parsing Error: Unexpected token %s\n", token.value);
	exit(EXIT_FAILURE);
}

NodeExpr expr_create(Token token) {
	NodeExpr expr;
	expr.type = set_expr_type(token);
	expr.token = token;
	return expr;
}

NodeStmtExit exit_create(NodeExpr expr) {
	NodeStmtExit ext;
	ext.expr = expr;
	return ext;
}

NodeStmtRet ret_create(NodeExpr expr) {
	NodeStmtRet ret;
	ret.expr = expr;
	return ret;
}

NodeStmtType type_create(NodeExpr expr, Token idnt) {
	NodeStmtType type;
	type.expr = expr;
	type.idnt = idnt;
	return type;
}

StmtType set_stmt_type(Token token) {
	switch (token.type) {
		case _exit:
			return stmt_exit;
		case _ret:
			return stmt_ret;
		case _type:
			return stmt_type;
		default:
			// If token does not have a valid type, should be impossible
			fprintf(stderr, "Parsing Error: Unexpected token %s\n", token.value);
			exit(EXIT_FAILURE);
	}

	// If token does not have a valid type, should be impossible
	fprintf(stderr, "Parsing Error: Unexpected token %s\n", token.value);
	exit(EXIT_FAILURE);
}

NodeStmt stmt_create(Token token, NodeExpr expr) {
	NodeStmt stmt;
	stmt.type = set_stmt_type(token);
	stmt.expr = expr;

	// Assign variant
	switch (stmt.type) {
		case stmt_exit:
			stmt.var.node_exit = exit_create(expr);
			break;
		case stmt_ret:
			stmt.var.node_ret = ret_create(expr);
			break;
		case stmt_type:
			stmt.var.node_type = type_create(expr, token);
			break;
		default:
			// If token does not have a valid type, should be impossible
			fprintf(stderr, "Parsing Error: Unexpected token %s\n", token.value);
			exit(EXIT_FAILURE);
	}

	return stmt;
}

int parse_expr(TokenStack* stack, Token* curr_token, NodeExpr* out_expr) {
	// Integer type expression
	if (token_peek(stack, curr_token) && curr_token->type == _int) {
		*out_expr = expr_create(*curr_token);
		token_consume(stack, curr_token);
		return 1; // success
	// Identifier type expression
	} else if (token_peek(stack, curr_token) && curr_token->type == _idnt) {
		*out_expr = expr_create(*curr_token);
		token_consume(stack, curr_token);
		return 1; // success
	// Invalid expression
	} else {
		return 0; // fail
	}
}

// TODO: Refactor to use switch statements and a central semi-colon checking system
int parse_stmt(TokenStack* stack, Token* curr_token, Token* ahd_token, NodeExpr* out_expr, NodeStmt* out_stmt) {
	Token ahdahd_token;
	Token stmt_keyword = *curr_token;

	// Exit statement
	if (curr_token->type == _exit && token_peekAhead(stack, 1, ahd_token)
			&& ahd_token->type == _oparen) { // Exit node
		token_consume(stack, curr_token); // Consume exit
		token_consume(stack, curr_token); // Consume open paren
		if (parse_expr(stack, curr_token, out_expr)) {
			// Parse expression and pass to exit statement
			*out_stmt = stmt_create(stmt_keyword, *out_expr);
		} else {
			fprintf(stderr, "Parsing Error: Expected expression in 'exit'\n");
			exit(EXIT_FAILURE);
		}

		// Check if next token is close paren
		if (token_peek(stack, curr_token) && curr_token->type == _cparen) {
			token_consume(stack, curr_token);
		} else {
			fprintf(stderr, "Parsing Error: Expected ')' after expression\n");
			exit(EXIT_FAILURE);
		}

		// Check if next token is the semi-colon
		if (token_peek(stack, curr_token) && curr_token->type == _semi) {
			token_consume(stack, curr_token);
		} else {
			fprintf(stderr, "Parsing Error: Expected ';' after statement\n");
			exit(EXIT_FAILURE);
		}

	// Return statement
	} else if (curr_token->type == _ret) {
		token_consume(stack, curr_token); // Consume 'return'
		if (parse_expr(stack, curr_token, out_expr)) {
			// Parse expression and pass to return statement
			*out_stmt = stmt_create(stmt_keyword, *out_expr);
		} else {
			fprintf(stderr, "Parsing Error: Expected expression after 'return'\n");
			exit(EXIT_FAILURE);
		}

		// Check if next token is the semi-colon
		if (token_peek(stack, curr_token) && curr_token->type == _semi) {
			token_consume(stack, curr_token);
		} else {
			fprintf(stderr, "Parsing Error: Expected ';' after statement\n");
			exit(EXIT_FAILURE);
		}

	// Type declaration
	} else if (curr_token->type == _type
			&& token_peekAhead(stack, 1, ahd_token)
			&& ahd_token->type == _idnt
			&& token_peekAhead(stack, 2, &ahdahd_token)
			&& ahdahd_token.type == _eq) {
		token_consume(stack, curr_token); // Consume type
		Token idnt = *curr_token; // Store identifier
		token_consume(stack, curr_token); // Consume idnt
		token_consume(stack, curr_token); // Consume equals
		if (parse_expr(stack, curr_token, out_expr)) {
			// Parse expression and pass to type statement
			*out_stmt = stmt_create(idnt, *out_expr);
		} else {
			fprintf(stderr, "Parsing Error: Invalid expression %s\n", out_expr->token.value);
			exit(EXIT_FAILURE);
		}
		if (curr_token->type == _semi) {
			token_consume(stack, curr_token); // Consume semi-colon
		} else {
			fprintf(stderr, "Parsing Error: Expected ';' after statement\n");
			exit(EXIT_FAILURE);
		}
	}
	return 1; // success
}

void add_to_main(NodeMain* out_main, NodeStmt stmt, size_t* out_count) {
	// If no error, increment count
	(*out_count)++;
	// Allocate memory for new statement
	out_main->stmts = safe_realloc(out_main->stmts, (*out_count) * sizeof(NodeStmt));
	// Add new statement to statements array
	out_main->stmts[*out_count - 1] = stmt;
}

NodeMain parse(Parser parser, size_t* out_stmt_count) {
	// Initialize Token array
	Token* tokens = parser.tokens;

	// Restore retrieved count
	size_t count = parser.count;

	// Initialize Token Stack
	TokenStack stack = token_stack_create(tokens, count);

	// Initialize current Token
	Token curr_token;

	// Initialize ahead Token
	Token ahd_token;

	// Initialize nodes
	NodeMain main;
	main.stmts = NULL;
	NodeExpr expr;
	NodeStmt stmt;

	// Iterate through token stack
	while(token_peek(&stack, &curr_token)) {

		// Check for end of file indicator
		if (curr_token.type == _eof) {
			break;
		}

		// Parse the current token into a statement
		if (parse_stmt(&stack, &curr_token, &ahd_token, &expr, &stmt)) {
			// If statement successfully parses, add to array
			add_to_main(&main, stmt, out_stmt_count);
		} else {
			fprintf(stderr, "Parsing Error: Invalid statement\n");
			exit(EXIT_FAILURE);
		}
	}
	return main;
}

