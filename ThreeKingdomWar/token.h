#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <iostream>

enum class TokenType
{
	ERROR,
	// �����
	PLUS,	// +
	MINUS,	// -
	MUL,	// *
	DIV,	// /
	ASSIGN,	// =

	// ��ʶ��
	LPAREN,	// (
	RPAREN, // )
	SEMICOLON,	// ;

	// ��������
	INT,	// ����
	FLOAT,	// ������
	BOOL,	// ����ֵ
	VOID,	// ��ֵ
	FUNC,	// ����
	
	// ������
	IDENTIFIER,	// ����
	ITERGER,	// ����
	EOF_TOKEN,	// �������


};

// ������
class Token
{
public:
	TokenType type;
	std::string value;
	Token(TokenType type, std::string value) : 
		type(type), value(value) { }

	friend std::ostream& operator<<(std::ostream& os, const Token& token);

};


extern std::ostream& operator<<(std::ostream& os, const Token& token)
{
	return os << "Token<" << static_cast<int>(token.type) << ", " << token.value << ">";
}

#endif // !_TOKEN_H_
