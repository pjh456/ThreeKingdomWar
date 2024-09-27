#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "token.h"
#include "lexer.h"

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer), current_token(lexer.get_next_token()) {}

    void parse(); // 解析入口

private:
    Lexer& lexer;
    Token current_token;

    int parse_statement();  // 解析语句
    int parse_expression(); // 解析表达式
    int parse_term();       // 解析项（乘法）
    int parse_factor();     // 解析因子（括号表达式）
    void advance();         // 移动到下一个token
};

#endif // !_PARSER_H_
