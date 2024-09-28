#include "parser.h"

void Parser::parse()
{
    while (current_token.type != TokenType::EOF_TOKEN)
    {
        switch (current_token.type){
        case TokenType::FUNC:
            parse_function_declearation();  // 处理函数声明
            break;

        case TokenType::INT:
        case TokenType::FLOAT:
        case TokenType::BOOL:
        case TokenType::VOID:
        case TokenType::STRING:
        case TokenType::LIST:

        case TokenType::IDENTIFIER:
            parse_statement(); // 处理变量声明或赋值
            break;

        case TokenType::LBRACE:
            // 处理代码块
            eat(TokenType::LBRACE);
            // 继续解析代码块内容
            while (current_token.type != TokenType::RBRACE)
                parse_statement(); // 可以处理语句
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
    eat(TokenType::IDENTIFIER); // 函数名
    eat(TokenType::LPAREN); // 左括号

    /* 我可能不打算制作带参带返回值的函数
    // 处理参数
    std::vector<std::pair<TokenType, std::string> > parameters; // 存储参数类型和名称
    while (current_token.type != TokenType::RPAREN) {
        eat(current_token.type); // 参数类型
        eat(TokenType::IDENTIFIER); // 参数名

        if (current_token.type == TokenType::COMMA) {
            eat(TokenType::COMMA); // 读取逗号
        }
    }
    */

    eat(TokenType::RPAREN); // 右括号
    eat(TokenType::LBRACE); // 左花括号

    // 简化处理，直接返回 1 表示函数解析成功
    while (current_token.type != TokenType::RBRACE)
    {
        parse_statement(); // 读取块中的内容
    }

    eat(TokenType::RBRACE); // 右花括号

    return 1; // 返回类型可以是函数的返回值类型
}

int Parser::parse_statement()
{
    // 处理变量赋值
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
                parse_expression(); // 解析赋值表达式
            }

            eat(TokenType::SEMICOLON); // 处理分号
            return 0;
        }
    }

    // 处理函数退出
    else if (current_token.type == TokenType::RETURN) {
        eat(TokenType::RETURN);
        eat(TokenType::SEMICOLON); // 读取分号
        return 0; // 返回结果
    }

    // 处理while循环
    else if (current_token.type == TokenType::WHILE)
    {
        eat(TokenType::WHILE);
        eat(TokenType::LPAREN);
        int condition_result = parse_expression(); // 假设条件表达式
        eat(TokenType::RPAREN);

        // 解析循环体
        eat(TokenType::LBRACE);
        while (condition_result) {
            parse_statement(); // 处理循环体
        }
        eat(TokenType::RBRACE);
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

        // TODO:处理循环体

        eat(TokenType::RBRACE);
    }
    // 处理条件语句
    else if (current_token.type == TokenType::IF) {
        eat(TokenType::IF);
        eat(TokenType::LPAREN);
        int condition_result = parse_expression(); // 假设条件表达式
        eat(TokenType::RPAREN);

        // 解析 if 体
        eat(TokenType::LBRACE);
        parse_statement(); // 处理 if 体
        eat(TokenType::RBRACE);

        // 可选的 else 处理
        if (current_token.type == TokenType::ELSE) {
            eat(TokenType::ELSE);
            eat(TokenType::LBRACE);
            parse_statement(); // 处理 else 体
            eat(TokenType::RBRACE);
        }
    }

    // 处理break
    else if (current_token.type == TokenType::BREAK)
    {
        eat(TokenType::BREAK);
        eat(TokenType::SEMICOLON);
        return 0; // 可以返回特定值表示break
    }

    // 处理continue
    else if (current_token.type == TokenType::CONTINUE)
    {
        eat(TokenType::CONTINUE);
        eat(TokenType::SEMICOLON);
        return 0; // 可以返回特定值表示continue
        }


    throw std::runtime_error("Expected a statement");
}

int Parser::parse_expression()
{
    int result = parse_term(); // 先处理项

    while (current_token.type == TokenType::PLUS || current_token.type == TokenType::MINUS)
    {
        Token op = current_token;
        eat(current_token.type);
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
        eat(current_token.type);
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
        eat(TokenType::INTEGER);
        return value;
    }
    else if (current_token.type == TokenType::IDENTIFIER) {
        std::string var_name = current_token.value;
        eat(TokenType::IDENTIFIER);
        // 假设你有一个方法 get_variable_value 来获取变量值
        //return get_variable_value(var_name); // 获取变量的值
        return 0;
    }
    else if (current_token.type == TokenType::LPAREN) {
        eat(TokenType::LPAREN);
        int result = parse_expression(); // 解析括号内的表达式
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
