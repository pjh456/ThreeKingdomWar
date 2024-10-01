#include "interpreter.h"

Interpreter::Interpreter()
{

}


void Interpreter::interpret(ASTNode* node)
{
    if (node)
        evaluate(node);
}

BlockNode* Interpreter::get_block() const
{
    return this->block;
}

void Interpreter::set_block(BlockNode* block)
{
    this->block = block;
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
    ASTNode* value_node = block->get(name);
    if (value_node) {
        evaluate(value_node);
    }
    else {
        std::cerr << "Error: Undefined variable " << name << std::endl;
    }
}

// ����ֵ
void Interpreter::handle_assignment(AssignmentNode* node) {
    const std::string& name = node->get_identifier()->get_name();
    ASTNode* value = node->get_value();
    evaluate(value); // ���㸳ֵ�ұߵ�ֵ
    block->define(name, value); // ���·��ű�

}

void Interpreter::handle_block(BlockNode* block)
{
    for (ASTNode* statement : block->get_statements())
        evaluate(statement);
}

ASTNode* Interpreter::evaluate_binary_expression(BinaryExpressionNode* node) {
    // �����Ԫ���ʽ�����磬�Ӽ��˳��ȣ�
    ASTNode* left = node->get_left();
    Token op = node->get_operator();
    ASTNode* right = node->get_right();

    evaluate(left);
    evaluate(right);

    float value = 0;
    // ������Ӿ���Ĳ���������ӷ���������
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

    return nullptr;
}

// ����һԪ���ʽ�����磬���ţ�
void Interpreter::evaluate_unary_expression(UnaryExpressionNode* node) {
    ASTNode* expression = node->get_expression();

    evaluate(expression);


    TokenType op = node->get_operator();

    switch (op) {
    case TokenType::MINUS:
        break;
    }
}

void Interpreter::handle_function_call(FunctionCallNode* node) {
    const std::string& name = node->get_name();
    const auto& arguments = node->get_arguments();

    std::cout << "Calling function: " << name << std::endl;

    for (ASTNode* arg : arguments) {
        evaluate(arg);
    }
}

// �����������
void Interpreter::handle_if_statement(IfStatementNode* node) {
    ASTNode* condition = node->get_condition();
    BlockNode* then_block = node->get_then_block();
    BlockNode* else_block = node->get_else_block();

    evaluate(condition);
}

void Interpreter::handle_while_statement(WhileStatementNode* node) {
    // ����ѭ�����
    ASTNode* condition = node->get_condition();
    BlockNode* block = node->get_block();

    // ѭ�����߼�
    // ������Ҫ��������жϺ�ѭ��ִ�е��߼�
}

// ����forѭ��
void Interpreter::handle_for_statement(ForStatementNode* node)
{
    IdentifierNode* object = node->get_object();
    ListNode* objects = node->get_objects();
    BlockNode* block = node->get_block();


}

// ���������
void Interpreter::handle_return_statement(ReturnStatementNode* node)
{

}