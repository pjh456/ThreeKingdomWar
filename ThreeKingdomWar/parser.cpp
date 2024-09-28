#include <algorithm>

#include "parser.h"

ASTNode* Parser::parse()
{
    std::vector<ASTNode*> statements;
    while (current_token.type != TokenType::EOF_TOKEN)
    {
        std::vector<ASTNode*> block_statements;

        switch (current_token.type){
        case TokenType::FUNC:
            statements.push_back(parse_function_declaration());  // ����������
            break;

        case TokenType::INT:
        case TokenType::FLOAT:
        case TokenType::BOOL:
        case TokenType::VOID:
        case TokenType::STRING:
        case TokenType::LIST:

        case TokenType::RETURN:
        case TokenType::WHILE:
        case TokenType::FOR:
        case TokenType::IF:
        case TokenType::ELSE:
        case TokenType::BREAK:
        case TokenType::CONTINUE:

        case TokenType::IDENTIFIER:
            statements.push_back(parse_statement()); // �������������ֵ
            break;

        // ��������
        case TokenType::LBRACE:
            eat(TokenType::LBRACE);

            while (current_token.type != TokenType::RBRACE)
                block_statements.push_back(parse_statement()); // ���Դ������

            statements.push_back(new BlockNode(block_statements));
            eat(TokenType::RBRACE);
            break;

        default:
            throw std::runtime_error("Unexpected token: " + current_token.value);
        }
    }
}

ASTNode* Parser::parse_function_declaration() 
{
    eat(TokenType::FUNC);
    
    std::string func_name = current_token.value;
    eat(TokenType::IDENTIFIER); // ������

    eat(TokenType::LPAREN); // ������

    std::vector<IdentifierNode*> parameters; // �洢����

    // �������������в���
    if (current_token.type != TokenType::RPAREN)
    {
        while (current_token.type != TokenType::RPAREN) {
            // ��ȡ��������
            TokenType param_type = current_token.type;
            eat(param_type);

            // ��ȡ��������
            if (current_token.type == TokenType::IDENTIFIER) {
                parameters.push_back(new IdentifierNode(current_token.value));
                eat(TokenType::IDENTIFIER);
            }

            if (current_token.type == TokenType::COMMA)
                eat(TokenType::COMMA);
            else break;
        }
    }

    eat(TokenType::RPAREN); // ������
    eat(TokenType::LBRACE); // ������

    std::vector<ASTNode*> statements;
    while (current_token.type != TokenType::RBRACE) {
        statements.push_back(parse_statement()); // ��ȡ���е�����
    }

    eat(TokenType::RBRACE); // �һ�����

    return new FunctionDeclarationNode(func_name, parameters, new BlockNode(statements)); // ���غ����ڵ�
}

ASTNode* Parser::parse_statement()
{
    // ���������ֵ
    if (current_token.type == TokenType::IDENTIFIER)
    {
        std::string var_name = current_token.value;
        eat(TokenType::IDENTIFIER);

        if (current_token.type == TokenType::ASSIGN)
        {
            eat(TokenType::ASSIGN);
            ASTNode* expr_result = parse_expression();
            eat(TokenType::SEMICOLON);

            return new AssignmentNode(new IdentifierNode(var_name), expr_result);
        }
        else if (current_token.type == TokenType::SEMICOLON)
        {
            eat(TokenType::SEMICOLON);
            return nullptr;
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
                ASTNode* expression = parse_expression(); // ������ֵ���ʽ
                eat(TokenType::SEMICOLON); // ����ֺ�

                return new AssignmentNode(new IdentifierNode(var_name), expression);
            }

            eat(TokenType::SEMICOLON); // ����ֺ�

            return nullptr;
            // ���ֻ�ǵ���һ�������õľ��ӾͲ�����
        }
    }

    // �������˳�
    else if (current_token.type == TokenType::RETURN) {
        eat(TokenType::RETURN);
        eat(TokenType::SEMICOLON); // ��ȡ�ֺ�
        return new ReturnStatementNode(); // ���ؽ��
    }

    // ����whileѭ��
    else if (current_token.type == TokenType::WHILE)
    {
        eat(TokenType::WHILE);
        eat(TokenType::LPAREN);
        ASTNode* condition_result = parse_expression(); // �����������ʽ
        eat(TokenType::RPAREN);

        // ����ѭ����
        eat(TokenType::LBRACE);
        std::vector<ASTNode*> statements;
        while(current_token.type !=TokenType::RBRACE)
            statements.push_back(parse_statement()); // ����ѭ����
        eat(TokenType::RBRACE);
        return new WhileStatementNode(condition_result, new BlockNode(statements));
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

        std::vector<ASTNode*> block_statements;
        while(current_token.type!=TokenType::RBRACE)
            block_statements.push_back(parse_statement());
        
        BlockNode* block_node = new BlockNode(block_statements);
        // TODO:����ѭ����

        eat(TokenType::RBRACE);

        return nullptr;
        //return new ASTNode();
        //return ForStatementNode(variable_manager.define(object_name, ), variable_manager.define(objects_name, ), block_node);
    }
    // �����������
    else if (current_token.type == TokenType::IF) {
        eat(TokenType::IF);
        eat(TokenType::LPAREN);
        ASTNode* condition_result = parse_expression(); // �����������ʽ
        eat(TokenType::RPAREN);

        // ���� if ��
        eat(TokenType::LBRACE);

        std::vector<ASTNode*> then_block_statements;

        while (current_token.type != TokenType::RBRACE)
            then_block_statements.push_back(parse_statement()); // ���� if ��
        BlockNode* then_block = new BlockNode(then_block_statements);

        eat(TokenType::RBRACE);

        // ��ѡ�� else ����
        BlockNode* else_block = nullptr; // ���� else ��
        if (current_token.type == TokenType::ELSE) {
            eat(TokenType::ELSE);
            eat(TokenType::LBRACE);

            std::vector<ASTNode*> else_block_statements;

            while(current_token.type!=TokenType::RBRACE)
                else_block_statements.push_back(parse_statement()); // ���� else ��
            else_block = new BlockNode(else_block_statements);

            eat(TokenType::RBRACE);
        }

        return new IfStatementNode(condition_result, then_block, else_block);
    }

    // ����break
    else if (current_token.type == TokenType::BREAK)
    {
        eat(TokenType::BREAK);
        eat(TokenType::SEMICOLON);
        return new BreakStatementNode(); // ���Է����ض�ֵ��ʾbreak
    }

    // ����continue
    else if (current_token.type == TokenType::CONTINUE)
    {
        eat(TokenType::CONTINUE);
        eat(TokenType::SEMICOLON);
        return new ContinueStatementNode(); // ���Է����ض�ֵ��ʾcontinue
    }

    // �����б�
    else if(current_token.type == TokenType::LBRACKET)
    {
        return parse_list(); // �����б�
    }

    throw std::runtime_error("Expected a statement");
}

ASTNode* Parser::parse_expression()
{
    ASTNode* left = parse_term(); // �ȴ�����

    while (current_token.type == TokenType::PLUS
        || current_token.type == TokenType::MINUS
        || current_token.type == TokenType::LESS_THAN 
        || current_token.type == TokenType::GREATER_THAN
        )
    {
        Token op = current_token;
        eat(current_token.type);
        ASTNode* right = parse_term(); // ������һ����

        left = new BinaryExpressionNode(left, op, right);
    }

    return left;
}

ASTNode* Parser::parse_term() {
    ASTNode* left = parse_factor(); // �ȴ�������

    while (current_token.type == TokenType::MUL || current_token.type == TokenType::DIV) {
        Token op = current_token;
        eat(current_token.type);
        ASTNode* right = parse_factor(); // ������һ������

        left = new BinaryExpressionNode(left, op, right);
    }

    return left;
}

ASTNode* Parser::parse_factor() 
{
    if (current_token.type == TokenType::INT_LITERAL)
    {
        int value = std::stoi(current_token.value); // ��ȡ����ֵ
        eat(TokenType::INT_LITERAL);
        return new IntegerNode(value);
    }
    else if (current_token.type == TokenType::FLOAT_LITERAL)
    {
        float value = std::stoi(current_token.value); // ��ȡ����ֵ
        eat(TokenType::FLOAT_LITERAL);
        return new FloatNode(value);
    }
    else if (current_token.type == TokenType::BOOL_LITERAL)
    {
        bool value = current_token.value == "True"; // ��ȡ����ֵ
        eat(TokenType::BOOL_LITERAL);
        return new BooleanNode(value);
    }
    else if (current_token.type == TokenType::STRING_LITERAL)
    {
        std::string value = current_token.value; // ��ȡ����ֵ
        eat(TokenType::STRING_LITERAL);
        return new StringNode(value);
    }

    else if (current_token.type == TokenType::IDENTIFIER) {
        std::string var_name = current_token.value;
        eat(TokenType::IDENTIFIER);
        return new IdentifierNode(var_name);
    }
    else if (current_token.type == TokenType::LPAREN) {
        eat(TokenType::LPAREN);
        ASTNode* result = parse_expression(); // ���������ڵı��ʽ
        eat(TokenType::RPAREN);
        return result;
    }
    else if(current_token.type != TokenType::EOF_TOKEN){
        throw std::runtime_error("Expected an integer or '('");
    }
    return 0;
}

ASTNode* Parser::parse_list()
{
    eat(TokenType::LBRACKET);
    std::vector<ASTNode*> elements;

    while (current_token.type != TokenType::RBRACKET)
    {
        elements.push_back(parse_expression()); // ����ÿ��Ԫ��
        if (current_token.type == TokenType::COMMA)
            eat(TokenType::COMMA);
        else if (current_token.type != TokenType::RBRACKET)
            throw std::runtime_error("Expected ',' or ']'");
    }

    eat(TokenType::RBRACKET);

    return new ListNode(elements); // �����б�ڵ�
}

void Parser::eat(TokenType expected_type) {
    if(current_token.type == expected_type)
        current_token = lexer.get_next_token();
    else
        throw std::runtime_error("Unexpected token: " + current_token.value);
}
