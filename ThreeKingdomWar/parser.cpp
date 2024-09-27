#include "parser.h"

void Parser::parse()
{
    while (current_token.type != TokenType::UNKNOWN) {
        int result = parse_statement(); // 解析语句
        std::cout << result << std::endl; // 输出结果

        // 检查分号
        if (current_token.type == TokenType::SEMICOLON) {
            advance(); // 移动到下一个token
        }
        else {
            throw std::runtime_error("Expected ';' after statement");
        }
    }
}

int Parser::parse_statement()
{
    return parse_expression(); // 处理表达式
}

int Parser::parse_expression()
{
    int result = parse_term(); // 先处理项

    while (current_token.type == TokenType::PLUS || current_token.type == TokenType::MINUS)
    {
        Token op = current_token;
        advance(); // 移动到下一个token
        int right = parse_term(); // 处理下一个项

        if (op.type == TokenType::PLUS)
            result += right; // 处理加法
        else
            result -= right; // 处理减法
    }

    return result;
}

int Parser::parse_term() {
    int result = parse_factor(); // 先处理因子

    while (current_token.type == TokenType::MUL || current_token.type == TokenType::DIV) {
        Token op = current_token;
        advance(); // 移动到下一个token
        int right = parse_factor(); // 处理下一个因子

        if (op.type == TokenType::MUL) {
            result *= right; // 处理乘法
        }
        else {
            result /= right; // 处理除法
        }
    }

    return result;
}

int Parser::parse_factor() {
    if (current_token.type == TokenType::INTEGER) {
        int value = std::stoi(current_token.value); // 获取整数值
        advance(); // 移动到下一个token
        return value;
    }
    else if (current_token.type == TokenType::LPAREN) {
        advance(); // 跳过左括号
        int result = parse_expression(); // 解析括号内的表达式
        if (current_token.type != TokenType::RPAREN) {
            throw std::runtime_error("Expected ')'");
        }
        advance(); // 移动到下一个token
        return result;
    }
    else if(current_token.type != TokenType::EOF_TOKEN){
        throw std::runtime_error("Expected an integer or '('");
    }
}

void Parser::advance() {
    current_token = lexer.get_next_token();
}
