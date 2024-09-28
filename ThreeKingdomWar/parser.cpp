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
            statements.push_back(parse_function_declaration());  // 处理函数声明
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
            statements.push_back(parse_statement()); // 处理变量声明或赋值
            break;

        // 处理代码块
        case TokenType::LBRACE:
            eat(TokenType::LBRACE);

            while (current_token.type != TokenType::RBRACE)
                block_statements.push_back(parse_statement()); // 可以处理语句

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
    eat(TokenType::IDENTIFIER); // 函数名

    eat(TokenType::LPAREN); // 左括号

    std::vector<IdentifierNode*> parameters; // 存储参数

    // 处理参数，如果有参数
    if (current_token.type != TokenType::RPAREN)
    {
        while (current_token.type != TokenType::RPAREN) {
            // 读取参数类型
            TokenType param_type = current_token.type;
            eat(param_type);

            // 读取参数名称
            if (current_token.type == TokenType::IDENTIFIER) {
                parameters.push_back(new IdentifierNode(current_token.value));
                eat(TokenType::IDENTIFIER);
            }

            if (current_token.type == TokenType::COMMA)
                eat(TokenType::COMMA);
            else break;
        }
    }

    eat(TokenType::RPAREN); // 右括号
    eat(TokenType::LBRACE); // 左花括号

    std::vector<ASTNode*> statements;
    while (current_token.type != TokenType::RBRACE) {
        statements.push_back(parse_statement()); // 读取块中的内容
    }

    eat(TokenType::RBRACE); // 右花括号

    return new FunctionDeclarationNode(func_name, parameters, new BlockNode(statements)); // 返回函数节点
}

ASTNode* Parser::parse_statement()
{
    // 处理变量赋值
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

    // 处理类型声明
    else if (  current_token.type == TokenType::INT 
            || current_token.type == TokenType::FLOAT 
            || current_token.type == TokenType::BOOL 
            || current_token.type == TokenType::VOID
            || current_token.type == TokenType::STRING
            || current_token.type == TokenType::LIST
        ) 
    {
        TokenType type = current_token.type; // 保存类型
        eat(current_token.type); // 读取类型

        if (current_token.type == TokenType::IDENTIFIER) {
            std::string var_name = current_token.value;
            eat(TokenType::IDENTIFIER); // 读取变量名

            if (current_token.type == TokenType::ASSIGN) {
                eat(TokenType::ASSIGN);
                ASTNode* expression = parse_expression(); // 解析赋值表达式
                eat(TokenType::SEMICOLON); // 处理分号

                return new AssignmentNode(new IdentifierNode(var_name), expression);
            }

            eat(TokenType::SEMICOLON); // 处理分号

            return nullptr;
            // 如果只是单独一个无作用的句子就不管了
        }
    }

    // 处理函数退出
    else if (current_token.type == TokenType::RETURN) {
        eat(TokenType::RETURN);
        eat(TokenType::SEMICOLON); // 读取分号
        return new ReturnStatementNode(); // 返回结果
    }

    // 处理while循环
    else if (current_token.type == TokenType::WHILE)
    {
        eat(TokenType::WHILE);
        eat(TokenType::LPAREN);
        ASTNode* condition_result = parse_expression(); // 假设条件表达式
        eat(TokenType::RPAREN);

        // 解析循环体
        eat(TokenType::LBRACE);
        std::vector<ASTNode*> statements;
        while(current_token.type !=TokenType::RBRACE)
            statements.push_back(parse_statement()); // 处理循环体
        eat(TokenType::RBRACE);
        return new WhileStatementNode(condition_result, new BlockNode(statements));
    }

    // 处理for循环
    else if (current_token.type == TokenType::FOR)
    {
        eat(TokenType::FOR);
        eat(TokenType::LPAREN);

        std::string object_name = current_token.value; // 对象名
        eat(TokenType::IDENTIFIER);
        eat(TokenType::COLON); // 处理冒号

        // 解析 objects
        std::string objects_name = current_token.value; // List 名称
        eat(TokenType::IDENTIFIER);

        eat(TokenType::RPAREN);

        // 解析循环体
        eat(TokenType::LBRACE);

        std::vector<ASTNode*> block_statements;
        while(current_token.type!=TokenType::RBRACE)
            block_statements.push_back(parse_statement());
        
        BlockNode* block_node = new BlockNode(block_statements);
        // TODO:处理循环体

        eat(TokenType::RBRACE);

        return nullptr;
        //return new ASTNode();
        //return ForStatementNode(variable_manager.define(object_name, ), variable_manager.define(objects_name, ), block_node);
    }
    // 处理条件语句
    else if (current_token.type == TokenType::IF) {
        eat(TokenType::IF);
        eat(TokenType::LPAREN);
        ASTNode* condition_result = parse_expression(); // 假设条件表达式
        eat(TokenType::RPAREN);

        // 解析 if 体
        eat(TokenType::LBRACE);

        std::vector<ASTNode*> then_block_statements;

        while (current_token.type != TokenType::RBRACE)
            then_block_statements.push_back(parse_statement()); // 处理 if 体
        BlockNode* then_block = new BlockNode(then_block_statements);

        eat(TokenType::RBRACE);

        // 可选的 else 处理
        BlockNode* else_block = nullptr; // 处理 else 体
        if (current_token.type == TokenType::ELSE) {
            eat(TokenType::ELSE);
            eat(TokenType::LBRACE);

            std::vector<ASTNode*> else_block_statements;

            while(current_token.type!=TokenType::RBRACE)
                else_block_statements.push_back(parse_statement()); // 处理 else 体
            else_block = new BlockNode(else_block_statements);

            eat(TokenType::RBRACE);
        }

        return new IfStatementNode(condition_result, then_block, else_block);
    }

    // 处理break
    else if (current_token.type == TokenType::BREAK)
    {
        eat(TokenType::BREAK);
        eat(TokenType::SEMICOLON);
        return new BreakStatementNode(); // 可以返回特定值表示break
    }

    // 处理continue
    else if (current_token.type == TokenType::CONTINUE)
    {
        eat(TokenType::CONTINUE);
        eat(TokenType::SEMICOLON);
        return new ContinueStatementNode(); // 可以返回特定值表示continue
    }

    // 处理列表
    else if(current_token.type == TokenType::LBRACKET)
    {
        return parse_list(); // 解析列表
    }

    throw std::runtime_error("Expected a statement");
}

ASTNode* Parser::parse_expression()
{
    ASTNode* left = parse_term(); // 先处理项

    while (current_token.type == TokenType::PLUS
        || current_token.type == TokenType::MINUS
        || current_token.type == TokenType::LESS_THAN 
        || current_token.type == TokenType::GREATER_THAN
        )
    {
        Token op = current_token;
        eat(current_token.type);
        ASTNode* right = parse_term(); // 处理下一个项

        left = new BinaryExpressionNode(left, op, right);
    }

    return left;
}

ASTNode* Parser::parse_term() {
    ASTNode* left = parse_factor(); // 先处理因子

    while (current_token.type == TokenType::MUL || current_token.type == TokenType::DIV) {
        Token op = current_token;
        eat(current_token.type);
        ASTNode* right = parse_factor(); // 处理下一个因子

        left = new BinaryExpressionNode(left, op, right);
    }

    return left;
}

ASTNode* Parser::parse_factor() 
{
    if (current_token.type == TokenType::INT_LITERAL)
    {
        int value = std::stoi(current_token.value); // 获取整数值
        eat(TokenType::INT_LITERAL);
        return new IntegerNode(value);
    }
    else if (current_token.type == TokenType::FLOAT_LITERAL)
    {
        float value = std::stoi(current_token.value); // 获取浮点值
        eat(TokenType::FLOAT_LITERAL);
        return new FloatNode(value);
    }
    else if (current_token.type == TokenType::BOOL_LITERAL)
    {
        bool value = current_token.value == "True"; // 获取布尔值
        eat(TokenType::BOOL_LITERAL);
        return new BooleanNode(value);
    }
    else if (current_token.type == TokenType::STRING_LITERAL)
    {
        std::string value = current_token.value; // 获取布尔值
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
        ASTNode* result = parse_expression(); // 解析括号内的表达式
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
        elements.push_back(parse_expression()); // 解析每个元素
        if (current_token.type == TokenType::COMMA)
            eat(TokenType::COMMA);
        else if (current_token.type != TokenType::RBRACKET)
            throw std::runtime_error("Expected ',' or ']'");
    }

    eat(TokenType::RBRACKET);

    return new ListNode(elements); // 返回列表节点
}

void Parser::eat(TokenType expected_type) {
    if(current_token.type == expected_type)
        current_token = lexer.get_next_token();
    else
        throw std::runtime_error("Unexpected token: " + current_token.value);
}
