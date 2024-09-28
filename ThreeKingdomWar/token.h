#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <iostream>

enum class TokenType
{
	UNKNOWN,

	// �����
	PLUS,	// +
	MINUS,	// -
	MUL,	// *
	DIV,	// /
	ASSIGN,	// =
	EQUAL,	// ==

	// ��ʶ��
	LPAREN,		// (
	RPAREN,		// )
	SEMICOLON,	// ;
	DEFINATION, // # ע��
	LBRACE,		// {
	RBRACE,		// }
	COMMA,		// ,
	COLON,		// :

	// ��������
	INT,	// ����
	FLOAT,	// ������
	BOOL,	// ����ֵ
	VOID,	// ��ֵ
	FUNC,	// ����
	STRING, // �ַ���
	LIST,	// �б�
	
	// ������
	IDENTIFIER,	// ����
	INTEGER,	// ����
	EOF_TOKEN,	// �������

	// �߼�����
	PLAYER,			// ���
	STATE,			// ״̬
	CARD,			// ����
	CARD_CONTAINER,	// �ƶ�

	// �����ؼ���
	IF,
	ELSE,
	WHILE,
	FOR,
	CONTINUE,
	BREAK,
	RETURN,
	TRUE,
	FALSE,

	// ״̬�ؼ���
	BEFORE,
	WHEN,
	AFTER

};

// ������
class Token
{
public:
	TokenType type;
	std::string value;
	Token(TokenType type, std::string value) : 
		type(type), value(value) { }

	bool operator==(const Token& other) const 
	{
		return type == other.type && value == other.value;
	}

	friend std::ostream& operator<<(std::ostream& os, const Token& token)
	{
		return os << "Token<" << static_cast<int>(token.type) << ", " << token.value << ">";
	}

};

#endif // !_TOKEN_H_
