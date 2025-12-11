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
 * @brief Node for expressions.
 */
typedef struct {
	// Type
	ExprType type;
	
	// Token
	Token token;
} NodeExpr;

/**
 * @brief Enumerates the possible types of statements.
 */
typedef enum {
	stmt_invalid = 0,
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
	Token idnt;
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
	} var;
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
 * @brief Sets the expression type.
 */
ExprType set_expr_type(Token token);

/**
 * @brief Constructs expression node.
 */
NodeExpr expr_create(Token token);

/**
 * @brief Constructs an exit statement node.
 */
NodeStmtExit exit_create(NodeExpr expr);

/**
 * @brief Constructs a return statement node.
 */
NodeStmtRet ret_create(NodeExpr expr);

/**
 * @brief Constructs a type declaration / variable node.
 */
NodeStmtType type_create(NodeExpr expr, Token idnt);

/**
 * @brief Sets statement type.
 */
StmtType set_stmt_type(Token token);

/**
 * @brief Constructs a statement node.
 */
NodeStmt stmt_create(Token token, NodeExpr expr);

/**
 * @brief Parses statements into a program.
 */
NodeMain parse(Parser parser, size_t* out_stmt_count);

#endif // Closes PARSER_H include guard
