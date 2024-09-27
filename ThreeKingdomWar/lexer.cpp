#include "lexer.h"

Lexer::Lexer(const std::string& text) :
	input(text)
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
		}

		// 抽象定义无固定形态
	}
}

Lexer::~Lexer() = default;	// 这里以后可能要销毁AC自动机

Token Lexer::get_next_token()
{
	std::string  buffer;
	TokenType type = TokenType::UNKNOWN;

	// 跳过空格
	while (isspace(current_char))
		this->read_char();

	// 尝试读取多字符标记
	while (isalnum(current_char) || current_char == '_' || current_char == '=')
	{
		buffer.push_back(current_char);
		this->read_char();
		type = ac_automaton->find_key(buffer);

		if (type != TokenType::UNKNOWN)
			break;
	}

	if (type == TokenType::UNKNOWN)
	{
		if (isdigit(current_char))
		{
			do
			{
				buffer.push_back(current_char);
				this->read_char();
			}
			while (isdigit(current_char));
			return Token(TokenType::ITERGER, buffer);
		}
		else if (isalpha(current_char))
		{
			do
			{
				buffer.push_back(current_char);
				this->read_char();
			} while (isalpha(current_char));
			return Token(TokenType::IDENTIFIER, buffer);
		}
		else
		{
			std::cerr << "Unknown Token '" << buffer << "'" << std::endl;
			this->read_char();
		}

		return Token(type, buffer);
	}
}

void Lexer::read_char()
{
	current_char = (read_position >= input.length()) ? 0 : input[read_position];
	position = read_position++;
}

