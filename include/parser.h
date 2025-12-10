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
	size_t count;
} Parser;

/**
 * @brief Enumerates the possible types of expressions.
 */
typedef enum {
	expr_int,
	expr_idnt
} ExprType;

/**
 * @brief Node for integer literals.
 */
typedef struct {
	Token token;
} NodeInt;

/**
 * @brief Node for variable identifiers.
 */
typedef struct {
	Token token;
} NodeIdnt;

/**
 * @brief Node for expressions.
 */
typedef struct {
	// Active type
	ExprType type;
	
	// Primary token
	Token token;

	// Union of expression types
	union {
		NodeInt node_int;
		NodeIdnt node_idnt;
	} as;
} NodeExpr;

/**
 * @brief Node for return command.
 */
typedef struct {
	NodeExpr expr;
} NodeRet;

/**
 * @brief Enumerates the possible types of statements.
 */
typedef enum {
	stmt_exit,
	stmt_ret,
	stmt_type
} StmtType;

typedef struct {
	NodeExpr expr;
} NodeStmtExit;

typedef struct {
	NodeExpr expr;
} NodeStmtRet;

typedef struct {
	Token ident;
	NodeExpr expr;
} NodeStmtType;

/**
 * @brief Node for statements.
 */
typedef struct {
	// Active type
	StmtType type;

	// Primary expression
	NodeExpr expr;

	// Union of statement types
	union {
		NodeStmtExit node_exit;
		NodeStmtRet node_ret;
		NodeStmtType node_type;
	} as;
} NodeStmt;

/**
 * @brief Node for main entry point.
 */
typedef struct {
	NodeStmt* stmts;
} NodeMain;

/**
 * @brief Parse tree constructor.
 */
Parser parser_create(Token* tokens, size_t count);

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
