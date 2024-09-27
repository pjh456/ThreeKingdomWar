#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <iostream>

enum class TokenType
{
	UNKNOWN,

	// 运算符
	PLUS,	// +
	MINUS,	// -
	MUL,	// *
	DIV,	// /
	ASSIGN,	// =
	EQUAL,	// ==

	// 标识符
	LPAREN,	// (
	RPAREN, // )
	SEMICOLON,	// ;
	DEFINATION, // # 注释

	// 变量类型
	INT,	// 整数
	FLOAT,	// 浮点数
	BOOL,	// 布尔值
	VOID,	// 空值
	FUNC,	// 函数
	STRING, // 字符串
	
	// 抽象定义
	IDENTIFIER,	// 变量
	INTEGER,	// 数字
	EOF_TOKEN,	// 结束标记

	// 高级类型
	PLAYER,			// 玩家
	STATE,			// 状态
	CARD,			// 卡牌
	CARD_CONTAINER	// 牌堆

};

// 语义标记
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
