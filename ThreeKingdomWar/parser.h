#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "token.h"
#include "lexer.h"
#include "variable_manager.h"

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer), current_token(lexer.get_next_token()) {}

    void parse(); // 解析入口

private:
    Lexer& lexer;
    Token current_token;
    VariableManager variable_manager;

    int parse_function_declearation(); //解析函数声明


    int parse_statement();  // 解析语句
    int parse_expression(); // 解析表达式
    int parse_term();       // 解析项（乘法）
    int parse_factor();     // 解析因子（括号表达式）
    void eat(TokenType expected_type);         // 预期token消耗
};

#endif // !_PARSER_H_
