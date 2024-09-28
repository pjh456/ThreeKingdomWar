#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "token.h"
#include "lexer.h"
#include "ast_nodes.h"

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer), current_token(lexer.get_next_token()) {}

    ASTNode* parse(); // 解析入口

private:
    Lexer& lexer;
    Token current_token;

    ASTNode* parse_function_declaration(); //解析函数声明


    ASTNode* parse_statement();  // 解析语句
    ASTNode* parse_expression(); // 解析表达式
    ASTNode* parse_term();       // 解析项（乘法）
    ASTNode* parse_factor();     // 解析因子（括号表达式）
    ASTNode* parse_list();
    void eat(TokenType expected_type);         // 预期token消耗
};

#endif // !_PARSER_H_
