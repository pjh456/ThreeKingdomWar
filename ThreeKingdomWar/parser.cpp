#include "parser.h"

void Parser::parse()
{
    while (current_token.type != TokenType::UNKNOWN) {
        int result = parse_statement(); // �������
        std::cout << result << std::endl; // ������

        // ���ֺ�
        if (current_token.type == TokenType::SEMICOLON) {
            advance(); // �ƶ�����һ��token
        }
        else {
            throw std::runtime_error("Expected ';' after statement");
        }
    }
}

int Parser::parse_statement()
{
    return parse_expression(); // ������ʽ
}

int Parser::parse_expression()
{
    int result = parse_term(); // �ȴ�����

    while (current_token.type == TokenType::PLUS || current_token.type == TokenType::MINUS)
    {
        Token op = current_token;
        advance(); // �ƶ�����һ��token
        int right = parse_term(); // ������һ����

        if (op.type == TokenType::PLUS)
            result += right; // ����ӷ�
        else
            result -= right; // �������
    }

    return result;
}

int Parser::parse_term() {
    int result = parse_factor(); // �ȴ�������

    while (current_token.type == TokenType::MUL || current_token.type == TokenType::DIV) {
        Token op = current_token;
        advance(); // �ƶ�����һ��token
        int right = parse_factor(); // ������һ������

        if (op.type == TokenType::MUL) {
            result *= right; // ����˷�
        }
        else {
            result /= right; // �������
        }
    }

    return result;
}

int Parser::parse_factor() {
    if (current_token.type == TokenType::INTEGER) {
        int value = std::stoi(current_token.value); // ��ȡ����ֵ
        advance(); // �ƶ�����һ��token
        return value;
    }
    else if (current_token.type == TokenType::LPAREN) {
        advance(); // ����������
        int result = parse_expression(); // ���������ڵı��ʽ
        if (current_token.type != TokenType::RPAREN) {
            throw std::runtime_error("Expected ')'");
        }
        advance(); // �ƶ�����һ��token
        return result;
    }
    else if(current_token.type != TokenType::EOF_TOKEN){
        throw std::runtime_error("Expected an integer or '('");
    }
}

void Parser::advance() {
    current_token = lexer.get_next_token();
}
