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

    void parse(); // �������

private:
    Lexer& lexer;
    Token current_token;

    int parse_statement();  // �������
    int parse_expression(); // �������ʽ
    int parse_term();       // ������˷���
    int parse_factor();     // �������ӣ����ű��ʽ��
    void advance();         // �ƶ�����һ��token
};

#endif // !_PARSER_H_
