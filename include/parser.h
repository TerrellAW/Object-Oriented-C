// Include Guard, prevents compilation errors
#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "tokenizer.h"
#include "token_stack.h"

/**
 * @brief Parse tree data structure.
 */
typedef struct {
	Token* tokens;
} Parser;

/**
 * @brief Node for expressions.
 */
typedef struct {
	Token token;
} NodeExpr;

/**
 * @brief Node for return command.
 */
typedef struct {
	NodeExpr expr;
} NodeRet;

/**
 * @brief Node for exit command.
 */
typedef struct {
	NodeExpr expr;
} NodeExit;

/**
 * @brief Parse tree constructor.
 */
Parser parser_create(Token* tokens);

/**
 * @brief Constructs expression node.
 */
NodeExpr expr_create(Token token);

/**
 * @brief Constructs return node.
 */
NodeRet ret_create(NodeExpr expr);

/**
 * @brief Constructs exit node.
 */
NodeExit exit_create(NodeExpr expr);

/**
 * @brief Parses tokens using parse tree.
 */
NodeExit parse(Parser parser);

#endif // Closes PARSER_H include guard
