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
	LPAREN,	// (
	RPAREN, // )
	SEMICOLON,	// ;
	DEFINATION, // # ע��

	// ��������
	INT,	// ����
	FLOAT,	// ������
	BOOL,	// ����ֵ
	VOID,	// ��ֵ
	FUNC,	// ����
	STRING, // �ַ���
	
	// ������
	IDENTIFIER,	// ����
	INTEGER,	// ����
	EOF_TOKEN,	// �������

	// �߼�����
	PLAYER,			// ���
	STATE,			// ״̬
	CARD,			// ����
	CARD_CONTAINER	// �ƶ�

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

	friend std::ostream& operator<<(std::ostream& os, const Token& token);

};
#endif // !_TOKEN_H_
