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

    ASTNode* parse(); // �������

private:
    Lexer& lexer;
    Token current_token;

    ASTNode* parse_function_declaration(); //������������


    ASTNode* parse_statement();  // �������
    ASTNode* parse_expression(); // �������ʽ
    ASTNode* parse_term();       // ������˷���
    ASTNode* parse_factor();     // �������ӣ����ű��ʽ��
    ASTNode* parse_list();
    void eat(TokenType expected_type);         // Ԥ��token����
};

#endif // !_PARSER_H_
