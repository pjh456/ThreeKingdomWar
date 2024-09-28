#include "interpreter.h"

Interpreter::Interpreter()
{

}

void Interpreter::interpret(ASTNode* node)
{
    if (node)
        evaluate(node);
}

void Interpreter::evaluate(ASTNode* node)
{
    switch (node->get_type()) {
    case ASTNodeType::INTEGER:
        std::cout << static_cast<IntegerNode*>(node)->get_value() << std::endl;
        break;
    case ASTNodeType::FLOAT:
        std::cout << static_cast<FloatNode*>(node)->get_value() << std::endl;
        break;
    case ASTNodeType::STRING:
        std::cout << static_cast<StringNode*>(node)->get_value() << std::endl;
        break;
    case ASTNodeType::BOOL:
        std::cout << (static_cast<BooleanNode*>(node)->get_value() ? "true" : "false") << std::endl;
        break;
    case ASTNodeType::IDENTIFIER:
        handle_identifier(static_cast<IdentifierNode*>(node));
        break;
    case ASTNodeType::BINARY_EXPRESSION:
        evaluate_binary_expression(static_cast<BinaryExpressionNode*>(node));
        break;
    case ASTNodeType::UNARY_EXPRESSION:
        evaluate_unary_expression(static_cast<UnaryExpressionNode*>(node));
        break;
    case ASTNodeType::ASSIGNMENT:
        handle_assignment(static_cast<AssignmentNode*>(node));
        break;
    case ASTNodeType::BLOCK:
        handle_block(static_cast<BlockNode*>(node));
        break;
    case ASTNodeType::FUNCTION_CALL:
        handle_function_call(static_cast<FunctionCallNode*>(node));
        break;
    case ASTNodeType::IF_STATEMENT:
        handle_if_statement(static_cast<IfStatementNode*>(node));
        break;
    case ASTNodeType::WHILE_STATEMENT:
        handle_while_statement(static_cast<WhileStatementNode*>(node));
        break;
    case ASTNodeType::FOR_STATEMENT:
        handle_for_statement(static_cast<ForStatementNode*>(node));
        break;
    case ASTNodeType::RETURN_STATEMENT:
        handle_return_statement(static_cast<ReturnStatementNode*>(node));
        break;
    default:
        throw std::runtime_error("Unknown ASTNode type");
    }
}

void Interpreter::handle_identifier(IdentifierNode* node) {
    const std::string& name = node->get_name();
    ASTNode* value_node = variable_table.get(name);
    if (value_node) {
        evaluate(value_node);
    }
    else {
        std::cerr << "Error: Undefined variable " << name << std::endl;
    }
}

void Interpreter::handle_assignment(AssignmentNode* node) {
    const std::string& name = node->get_identifier()->get_name();
    ASTNode* value = node->get_value();
    evaluate(value); // 计算赋值右边的值
    variable_table.define(name, value); // 更新符号表
}

void Interpreter::handle_block(BlockNode* block) {
    for (ASTNode* statement : block->get_statements())
        evaluate(statement);
}

ASTNode* Interpreter::evaluate_binary_expression(BinaryExpressionNode* node) {
    // 处理二元表达式（例如，加减乘除等）
    ASTNode* left = node->get_left();
    Token op = node->get_operator();
    ASTNode* right = node->get_right();

    evaluate(left);
    evaluate(right);

    float value = 0;
    // 这里添加具体的操作，例如加法、减法等
    switch (op.type) {
    case TokenType::PLUS:
        break;
    case TokenType::MINUS:
        break;
    case TokenType::MUL:
        break;
    case TokenType::DIV:
        break;
    case TokenType::LESS_THAN:
        break;
    case TokenType::GREATER_THAN:
        break;
    }
}

void Interpreter::evaluate_unary_expression(UnaryExpressionNode* node) {
    // 处理一元表达式（例如，负号）
    ASTNode* expression = node->get_expression();
    evaluate(expression);
    // 这里添加具体的操作
    TokenType op = node->get_operator();

    switch (op) {
    case TokenType::MINUS:
        break;
    default:

    }
}

void Interpreter::handle_function_call(FunctionCallNode* node) {
    const std::string& name = node->get_name();
    const auto& arguments = node->get_arguments();

    // 在这里查找并调用对应的函数
    // 你可以在符号表中存储函数的信息
    std::cout << "Calling function: " << name << std::endl;

    for (ASTNode* arg : arguments) {
        evaluate(arg);
    }
}

void Interpreter::handle_if_statement(IfStatementNode* node) {
    // 处理条件语句
    ASTNode* condition = node->get_condition();
    BlockNode* then_block = node->get_then_block();
    BlockNode* else_block = node->get_else_block();

    evaluate(condition); // 计算条件

    // 根据条件的值决定执行哪个代码块
    // 这里需要增加条件判断的逻辑
}

void Interpreter::handle_while_statement(WhileStatementNode* node) {
    // 处理循环语句
    ASTNode* condition = node->get_condition();
    BlockNode* block = node->get_block();

    // 循环的逻辑
    // 这里需要添加条件判断和循环执行的逻辑
}

void Interpreter::handle_for_statement(ForStatementNode* node) {
    // 处理for循环
    IdentifierNode* object = node->get_object();
    IdentifierNode* objects = node->get_objects();
    BlockNode* block = node->get_block();

    // 循环的逻辑
    // 这里需要添加循环执行的逻辑
}

void Interpreter::handle_return_statement(ReturnStatementNode* node) {
    // 处理返回语句
    // 这里可以处理返回值逻辑
}