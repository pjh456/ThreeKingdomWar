#include "lexer.h"

Lexer::Lexer(const std::string& text) :
	input(text), current_char(text[0])
{
	this->read_char();
	ac_automaton = new ACAutoMaton();

	// 初始化AC自动机节点
	{
		// 运算符
		{
			ac_automaton->add_key("+", TokenType::PLUS);
			ac_automaton->add_key("-", TokenType::MINUS);
			ac_automaton->add_key("*", TokenType::MUL);
			ac_automaton->add_key("/", TokenType::DIV);
			ac_automaton->add_key("=", TokenType::ASSIGN);
		}

		// 标识符
		{
			ac_automaton->add_key("(", TokenType::LPAREN);
			ac_automaton->add_key(")", TokenType::RPAREN);
			ac_automaton->add_key(";", TokenType::SEMICOLON);
            // 注释直接判断就行
            ac_automaton->add_key("{", TokenType::LBRACE);
            ac_automaton->add_key("}", TokenType::RBRACE);
            ac_automaton->add_key(",", TokenType::COMMA);
            ac_automaton->add_key(":", TokenType::COLON);
		}

		// 变量类型
		{
			ac_automaton->add_key("Int", TokenType::INT);
			ac_automaton->add_key("Float", TokenType::FLOAT);
			ac_automaton->add_key("Bool", TokenType::BOOL);
			ac_automaton->add_key("Void", TokenType::VOID);
			ac_automaton->add_key("Func", TokenType::FUNC);
            ac_automaton->add_key("Str", TokenType::STRING);
		}

		// 抽象定义无固定形态

        // 高级类型
        {
            ac_automaton->add_key("Player", TokenType::PLAYER);
            ac_automaton->add_key("State", TokenType::STATE);
            ac_automaton->add_key("Card", TokenType::CARD);
            ac_automaton->add_key("CardContainer", TokenType::CARD_CONTAINER);
        }

        // 保留关键字
        {
            ac_automaton->add_key("if", TokenType::IF);
            ac_automaton->add_key("else", TokenType::ELSE);
            ac_automaton->add_key("while", TokenType::WHILE);
            ac_automaton->add_key("for", TokenType::FOR);
            ac_automaton->add_key("continue", TokenType::CONTINUE);
            ac_automaton->add_key("break", TokenType::BREAK);
            ac_automaton->add_key("return", TokenType::RETURN);
            ac_automaton->add_key("True", TokenType::TRUE);
            ac_automaton->add_key("False", TokenType::FALSE);
        }

        // 状态关键字
        {
            ac_automaton->add_key("before", TokenType::BEFORE);
            ac_automaton->add_key("when", TokenType::WHEN);
            ac_automaton->add_key("after", TokenType::AFTER);
        }
	}
}

Lexer::~Lexer() {
    delete ac_automaton; // 释放AC自动机
}

Token Lexer::get_next_token()
{
	std::string buffer;
	TokenType type = TokenType::UNKNOWN;

	// 跳过空格
	while (isspace(current_char))
		this->read_char();

    // 处理注释
    if (current_char == '#') 
    {
        while (current_char != '\n' && current_char != 0) {
            this->read_char();
        }
        return get_next_token(); // 继续读取下一个标记
    }

    // 处理字符串
    else if (current_char == '"' || current_char == '\'')
    {
        char quote_char = current_char;
        this->read_char();
        while (current_char != quote_char && current_char != 0) 
        {
            buffer.push_back(current_char);
            this->read_char();
        }
        if (current_char == quote_char) 
        {
            this->read_char();
            return Token(TokenType::STRING, buffer);
        }
        else 
        {
            std::cerr << "Error: 不匹配的字符串" << std::endl;
            return Token(TokenType::UNKNOWN, buffer);
        }
    }

    // 尝试读取多字符标记
    else if (isalpha(current_char) || current_char == '_')
    {
        while (isalpha(current_char) || current_char == '_' || isdigit(current_char))
        {
            buffer.push_back(current_char);
            this->read_char();
        }
        type = ac_automaton->find_key(buffer); // 使用AC自动机查找关键字
        if (type == TokenType::UNKNOWN)
            return Token(TokenType::IDENTIFIER, buffer); // 处理标识符
        else if (type == TokenType::FUNC)
        {
            this->read_char(); // 函数声明
            return Token(TokenType::FUNC, buffer);
        }
    }

    // 处理代码块
    else if (current_char == '{') 
    {
        this->read_char();
        return Token(TokenType::LBRACE, "{");
    }

    else if (current_char == '}') 
    {
        this->read_char();
        return Token(TokenType::RBRACE, "}");
    }

    // 处理数字
    else if (isdigit(current_char))
    {
        // 读取整数部分
        do 
        {
            buffer.push_back(current_char);
            this->read_char();
        } while (isdigit(current_char));

        // 处理小数点
        if (current_char == '.') 
        {
            buffer.push_back(current_char);
            this->read_char();
            while (isdigit(current_char)) 
            {
                buffer.push_back(current_char);
                this->read_char();
            }
            return Token(TokenType::FLOAT, buffer); // 返回浮点数
        }

        return Token(TokenType::INTEGER, buffer); // 返回整数
    }

    // 处理分号
    else if (current_char == ';')
    {
        this->read_char();
        return Token(TokenType::SEMICOLON, ";");
    }

    // 处理完所有token后，返回结束状态
    else if (current_char == 0)
        return Token(TokenType::EOF_TOKEN, "");

    // 处理单字符运算符和其他符号
    else
    {
        std::string symbol(1, current_char);
        type = ac_automaton->find_key(symbol);
        this->read_char();
        return Token(type, symbol);
    }


    return Token(type, buffer);
}

void Lexer::read_char()
{
	current_char = (read_position >= input.length()) ? 0 : input[read_position];
	position = read_position++;
}

