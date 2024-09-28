#include "parser.h"

void Parser::parse()
{
    while (current_token.type != TokenType::EOF_TOKEN)
    {
        switch (current_token.type){
        case TokenType::FUNC:
            parse_function_declearation();  // ����������
            break;

        case TokenType::INT:
        case TokenType::FLOAT:
        case TokenType::BOOL:
        case TokenType::VOID:
        case TokenType::STRING:
        case TokenType::LIST:

        case TokenType::IDENTIFIER:
            parse_statement(); // �������������ֵ
            break;

        case TokenType::LBRACE:
            // ��������
            eat(TokenType::LBRACE);
            // �����������������
            while (current_token.type != TokenType::RBRACE)
                parse_statement(); // ���Դ������
            eat(TokenType::RBRACE);
            break;

        default:
            throw std::runtime_error("Unexpected token: " + current_token.value);
        }
    }
}

int Parser::parse_function_declearation()
{
    eat(TokenType::FUNC);
    eat(TokenType::IDENTIFIER); // ������
    eat(TokenType::LPAREN); // ������

    /* �ҿ��ܲ������������δ�����ֵ�ĺ���
    // �������
    std::vector<std::pair<TokenType, std::string> > parameters; // �洢�������ͺ�����
    while (current_token.type != TokenType::RPAREN) {
        eat(current_token.type); // ��������
        eat(TokenType::IDENTIFIER); // ������

        if (current_token.type == TokenType::COMMA) {
            eat(TokenType::COMMA); // ��ȡ����
        }
    }
    */

    eat(TokenType::RPAREN); // ������
    eat(TokenType::LBRACE); // ������

    // �򻯴���ֱ�ӷ��� 1 ��ʾ���������ɹ�
    while (current_token.type != TokenType::RBRACE)
    {
        parse_statement(); // ��ȡ���е�����
    }

    eat(TokenType::RBRACE); // �һ�����

    return 1; // �������Ϳ����Ǻ����ķ���ֵ����
}

int Parser::parse_statement()
{
    // ���������ֵ
    if (current_token.type == TokenType::IDENTIFIER)
    {
        std::string var_name = current_token.value;
        eat(TokenType::IDENTIFIER);

        if (current_token.type == TokenType::ASSIGN)
        {
            eat(TokenType::ASSIGN);
            int expr_result = parse_expression();
            eat(TokenType::SEMICOLON);

            return expr_result;
        }
        else if (current_token.type == TokenType::SEMICOLON)
        {
            eat(TokenType::SEMICOLON);
            return 0;
        }
    }

    // ������������
    else if (  current_token.type == TokenType::INT 
            || current_token.type == TokenType::FLOAT 
            || current_token.type == TokenType::BOOL 
            || current_token.type == TokenType::VOID
            || current_token.type == TokenType::STRING
            || current_token.type == TokenType::LIST
        ) 
    {
        TokenType type = current_token.type; // ��������
        eat(current_token.type); // ��ȡ����

        if (current_token.type == TokenType::IDENTIFIER) {
            std::string var_name = current_token.value;
            eat(TokenType::IDENTIFIER); // ��ȡ������

            if (current_token.type == TokenType::ASSIGN) {
                eat(TokenType::ASSIGN);
                parse_expression(); // ������ֵ���ʽ
            }

            eat(TokenType::SEMICOLON); // ����ֺ�
            return 0;
        }
    }

    // �������˳�
    else if (current_token.type == TokenType::RETURN) {
        eat(TokenType::RETURN);
        eat(TokenType::SEMICOLON); // ��ȡ�ֺ�
        return 0; // ���ؽ��
    }

    // ����whileѭ��
    else if (current_token.type == TokenType::WHILE)
    {
        eat(TokenType::WHILE);
        eat(TokenType::LPAREN);
        int condition_result = parse_expression(); // �����������ʽ
        eat(TokenType::RPAREN);

        // ����ѭ����
        eat(TokenType::LBRACE);
        while (condition_result) {
            parse_statement(); // ����ѭ����
        }
        eat(TokenType::RBRACE);
    }

    // ����forѭ��
    else if (current_token.type == TokenType::FOR)
    {
        eat(TokenType::FOR);
        eat(TokenType::LPAREN);

        std::string object_name = current_token.value; // ������
        eat(TokenType::IDENTIFIER);
        eat(TokenType::COLON); // ����ð��

        // ���� objects
        std::string objects_name = current_token.value; // List ����
        eat(TokenType::IDENTIFIER);

        eat(TokenType::RPAREN);

        // ����ѭ����
        eat(TokenType::LBRACE);

        // TODO:����ѭ����

        eat(TokenType::RBRACE);
    }
    // �����������
    else if (current_token.type == TokenType::IF) {
        eat(TokenType::IF);
        eat(TokenType::LPAREN);
        int condition_result = parse_expression(); // �����������ʽ
        eat(TokenType::RPAREN);

        // ���� if ��
        eat(TokenType::LBRACE);
        parse_statement(); // ���� if ��
        eat(TokenType::RBRACE);

        // ��ѡ�� else ����
        if (current_token.type == TokenType::ELSE) {
            eat(TokenType::ELSE);
            eat(TokenType::LBRACE);
            parse_statement(); // ���� else ��
            eat(TokenType::RBRACE);
        }
    }

    // ����break
    else if (current_token.type == TokenType::BREAK)
    {
        eat(TokenType::BREAK);
        eat(TokenType::SEMICOLON);
        return 0; // ���Է����ض�ֵ��ʾbreak
    }

    // ����continue
    else if (current_token.type == TokenType::CONTINUE)
    {
        eat(TokenType::CONTINUE);
        eat(TokenType::SEMICOLON);
        return 0; // ���Է����ض�ֵ��ʾcontinue
        }


    throw std::runtime_error("Expected a statement");
}

int Parser::parse_expression()
{
    int result = parse_term(); // �ȴ�����

    while (current_token.type == TokenType::PLUS || current_token.type == TokenType::MINUS)
    {
        Token op = current_token;
        eat(current_token.type);
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
        eat(current_token.type);
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
        eat(TokenType::INTEGER);
        return value;
    }
    else if (current_token.type == TokenType::IDENTIFIER) {
        std::string var_name = current_token.value;
        eat(TokenType::IDENTIFIER);
        // ��������һ������ get_variable_value ����ȡ����ֵ
        //return get_variable_value(var_name); // ��ȡ������ֵ
        return 0;
    }
    else if (current_token.type == TokenType::LPAREN) {
        eat(TokenType::LPAREN);
        int result = parse_expression(); // ���������ڵı��ʽ
        eat(TokenType::RPAREN);
        return result;
    }
    else if(current_token.type != TokenType::EOF_TOKEN){
        throw std::runtime_error("Expected an integer or '('");
    }
    return 0;
}

void Parser::eat(TokenType expected_type) {
    if(current_token.type == expected_type)
        current_token = lexer.get_next_token();
    else
        throw std::runtime_error("Unexpected token: " + current_token.value);
}
