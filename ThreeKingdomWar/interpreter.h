#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <functional>
#include <unordered_map>

#include "token.h"
#include "lexer.h"
#include "ast_nodes.h"
#include "parser.h"
#include "variable_table.h"


class Interpreter
{
public:
    Interpreter();
    void interpret(ASTNode* node);

private:
    void evaluate(ASTNode* node);

    void handle_identifier(IdentifierNode* node);
    void handle_assignment(AssignmentNode* node);
    void handle_block(BlockNode* block);
    ASTNode* evaluate_binary_expression(BinaryExpressionNode* node);
    void evaluate_unary_expression(UnaryExpressionNode* node);
    void handle_function_call(FunctionCallNode* node);
    void handle_if_statement(IfStatementNode* node);
    void handle_while_statement(WhileStatementNode* node);
    void handle_for_statement(ForStatementNode* node);
    void handle_return_statement(ReturnStatementNode* node);

private:
    VariableTable variable_table;
};

#endif // !_INTERPRETER_H_
