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
    if (current_char == '#') {
        while (current_char != '\n' && current_char != 0) {
            this->read_char();
        }
        return get_next_token(); // 继续读取下一个标记
    }

    // 处理字符串
    if (current_char == '"' || current_char == '\'') {
        char quote_char = current_char;
        this->read_char();
        while (current_char != quote_char && current_char != 0) {
            buffer.push_back(current_char);
            this->read_char();
        }
        if (current_char == quote_char) {
            this->read_char();
            return Token(TokenType::STRING, buffer);
        }
        else {
            std::cerr << "Error: 不匹配的字符串" << std::endl;
            return Token(TokenType::UNKNOWN, buffer);
        }
    }

    // 尝试读取多字符标记
    if (isalpha(current_char) || current_char == '_')
    {
        while (isalpha(current_char) || current_char == '_' || isdigit(current_char))
        {
            buffer.push_back(current_char);
            this->read_char();
        }
        type = ac_automaton->find_key(buffer); // 使用AC自动机查找关键字
        if (type == TokenType::UNKNOWN)
        {
            return Token(TokenType::IDENTIFIER, buffer); // 处理标识符
        }
    }
    // 处理数字
    else if (isdigit(current_char)) {
        // 读取整数部分
        do {
            buffer.push_back(current_char);
            this->read_char();
        } while (isdigit(current_char));

        // 处理小数点
        if (current_char == '.') {
            buffer.push_back(current_char);
            this->read_char();
            while (isdigit(current_char)) {
                buffer.push_back(current_char);
                this->read_char();
            }
            return Token(TokenType::FLOAT, buffer); // 返回浮点数
        }

        return Token(TokenType::INTEGER, buffer); // 返回整数
    }
    // 添加分号处理
    else if (current_char == ';')
    {
        this->read_char();
        return Token(TokenType::SEMICOLON, ";");
    }
    // 处理单字符运算符和其他符号
    else {
        switch (current_char){
        case '+':
            this->read_char();
            return Token(TokenType::PLUS, "+");
        case '-':
            this->read_char();
            return Token(TokenType::MINUS, "-");
        case '*':
            this->read_char();
            return Token(TokenType::MUL, "*");
        case '/':
            this->read_char();
            return Token(TokenType::DIV, "/");
        case '(':
            this->read_char();
            return Token(TokenType::LPAREN, "(");
        case ')':
            this->read_char();
            return Token(TokenType::RPAREN, ")");
        case '=':
            buffer.push_back(current_char);
            this->read_char();
            if (current_char == '=')
            {
                buffer.push_back(current_char);
                this->read_char();
                return Token(TokenType::EQUAL, "==");
            }
            else
            {
                return Token(TokenType::ASSIGN, "=");
            }
        default:
            if (current_char != 0)
                std::cerr << "Unknown Token '" << current_char << "'" << std::endl;
            this->read_char();
            return Token(TokenType::UNKNOWN, buffer);
        }
    }

    // 处理完所有token后，返回结束状态
    if (current_char == 0)
        return Token(TokenType::EOF_TOKEN, "");

    return Token(type, buffer);
}

void Lexer::read_char()
{
	current_char = (read_position >= input.length()) ? 0 : input[read_position];
	position = read_position++;
}

