#include <stdio.h>

#include "../include/parser.h"
#include "../include/tokenizer.h"
#include "../include/token_stack.h"

Parser parser_create(Token* tokens) {
	Parser parser;
	parser.tokens = tokens;
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
	if (token_peak(stack, curr_token) && curr_token->type == _int) {
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

	// Initialize Token Stack
	TokenStack stack = token_stack_create(tokens);

	// Initialize current Token
	Token curr_token;

	// Initialize nodes
	NodeExit ext;
	NodeRet ret;
	NodeExpr expr;

	// Iterate through token stack
	while(token_peak(&stack, &curr_token)) {
		if (curr_token.type == _exit) { // Exit node
			token_consume(&stack, &curr_token);
			if (parse_expr(&stack, &curr_token, &expr) != 0) {
				// Parse expression and pass to exit node
				ext = exit_create(expr);
			} else {
				fprintf(stderr, "Invalid expression %s", curr_token.value);
				exit(EXIT_FAILURE);
			}
		}
		if (curr_token.type == _ret) { // Return node
			token_consume(&stack, &curr_token);
			if (parse_expr(&stack, &curr_token, &expr) != 0) {
				// Parse expression and pass to return node
				ret = ret_create(expr);
			} else {
				fprintf(stderr, "Invalid expression %s", curr_token.value);
				exit(EXIT_FAILURE);
			}
		}
		if (!token_peak(&stack, &curr_token) || curr_token.type != _semi) {
			fprintf(stderr, "Invalid expression %s", curr_token.value);
			exit(EXIT_FAILURE);
		}
	}
	return ext;
}

