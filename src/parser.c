#include <stdio.h>

#include "../include/parser.h"
#include "../include/tokenizer.h"
#include "../include/token_stack.h"

Parser parser_create(Token* tokens, size_t count) {
	Parser parser;
	parser.tokens = tokens;
	parser.count = count;
	return parser;
}

NodeExpr expr_create(Token token) {
	NodeExpr expr;
	expr.token = token;
	return expr;
}

NodeRet ret_create(NodeExpr expr) {
	NodeRet ret;
	ret.expr = expr;
	return ret;
}

NodeExit exit_create(NodeExpr expr) {
	NodeExit ext;
	ext.expr = expr;
	return ext;
}

int parse_expr(TokenStack* stack, Token* curr_token, NodeExpr* out_expr) {
	if (token_peek(stack, curr_token) && curr_token->type == _int) {
		*out_expr = expr_create(*curr_token);
		token_consume(stack, curr_token);
		return 1; // success
	} else {
		return 0; // fail
	}
}

NodeExit parse(Parser parser) {
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
	NodeExit ext;
	NodeRet ret;
	NodeExpr expr;

	// Iterate through token stack
	while(token_peek(&stack, &curr_token)) {
		if (curr_token.type == _exit && token_peekAhead(&stack, 1, &ahd_token)
				&& ahd_token.type == _oparen) { // Exit node
			token_consume(&stack, &curr_token); // Consume exit
			token_consume(&stack, &curr_token); // Consume open paren
			if (parse_expr(&stack, &curr_token, &expr)) {
				// Parse expression and pass to exit node
				ext = exit_create(expr);
			} else {
				fprintf(stderr, "Parsing Error: Expected expression in 'exit'\n");
				exit(EXIT_FAILURE);
			}
		} else if (curr_token.type == _ret) { // Return node
			token_consume(&stack, &curr_token);
			if (parse_expr(&stack, &curr_token, &expr)) {
				// Parse expression and pass to return node
				ret = ret_create(expr);
			} else {
				fprintf(stderr, "Parsing Error: Expected expression after 'return'\n");
				exit(EXIT_FAILURE);
			}
		} else { // Undefined token
			// Ensure token is not EOF
			if (curr_token.type == _eof) {
				// Ignore and break the loop
				break;
			}
			
			fprintf(stderr, "Parsing Error: Unexpected token %s\n", curr_token.value);
			exit(EXIT_FAILURE);
		}

		// Check if next token is close paren
		if (token_peek(&stack, &curr_token) && curr_token.type == _cparen) {
			token_consume(&stack, &curr_token);
		} else {
			fprintf(stderr, "Parsing Error: Expected ')' after expression\n");
			exit(EXIT_FAILURE);
		}

		// Check if next token is the semi-colon
		if (token_peek(&stack, &curr_token) && curr_token.type == _semi) {
			token_consume(&stack, &curr_token);
		} else {
			fprintf(stderr, "Parsing Error: Expected ';' after statement\n");
			exit(EXIT_FAILURE);
		}
	}
	return ext;
}

