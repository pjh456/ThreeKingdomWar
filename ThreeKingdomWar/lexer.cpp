#include "lexer.h"

Lexer::Lexer(const std::string& text) :
	input(text)
{
	this->read_char();
	ac_automaton = new ACAutoMaton();

	// ��ʼ��AC�Զ����ڵ�
	{
		// �����
		{
			ac_automaton->add_key("+", TokenType::PLUS);
			ac_automaton->add_key("-", TokenType::MINUS);
			ac_automaton->add_key("*", TokenType::MUL);
			ac_automaton->add_key("/", TokenType::DIV);
			ac_automaton->add_key("=", TokenType::ASSIGN);
		}

		// ��ʶ��
		{
			ac_automaton->add_key("(", TokenType::LPAREN);
			ac_automaton->add_key(")", TokenType::RPAREN);
			ac_automaton->add_key(";", TokenType::SEMICOLON);
		}

		// ��������
		{
			ac_automaton->add_key("Int", TokenType::INT);
			ac_automaton->add_key("Float", TokenType::FLOAT);
			ac_automaton->add_key("Bool", TokenType::BOOL);
			ac_automaton->add_key("Void", TokenType::VOID);
			ac_automaton->add_key("Func", TokenType::FUNC);
		}

		// �������޹̶���̬
	}
}

Lexer::~Lexer() = default;	// �����Ժ����Ҫ����AC�Զ���

Token Lexer::get_next_token()
{
	std::string  buffer;
	TokenType type = TokenType::UNKNOWN;

	// �����ո�
	while (isspace(current_char))
		this->read_char();

	// ���Զ�ȡ���ַ����
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

