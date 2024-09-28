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
	LESS_THAN,		// <
	GREATER_THAN,	// >

	// 标识符
	LPAREN,		// (
	RPAREN,		// )
	SEMICOLON,	// ;
	DEFINATION, // # 注释
	LBRACE,		// {
	RBRACE,		// }
	COMMA,		// ,
	COLON,		// :
	LBRACKET,	// [
	RBRACKET,	// ]

	// 变量类型
	INT,	// 整数类型
	FLOAT,	// 浮点数类型
	BOOL,	// 布尔值类型
	VOID,	// 空值类型
	FUNC,	// 函数类型
	STRING, // 字符串类型
	LIST,	// 列表类型

	// 常量类型
	INT_LITERAL,	// 整数
	FLOAT_LITERAL,	// 浮点数
	BOOL_LITERAL,	// 布尔值
	VOID_LITERAL,	// 空值
	FUNC_LITERAL,	// 函数
	STRING_LITERAL, // 字符串
	LIST_LITERAL,	// 列表
	
	// 抽象定义
	IDENTIFIER,	// 变量
	EOF_TOKEN,	// 结束标记

	// 高级类型
	PLAYER,			// 玩家
	STATE,			// 状态
	CARD,			// 卡牌
	CARD_CONTAINER,	// 牌堆

	// 保留关键字
	IF,
	ELSE,
	WHILE,
	FOR,
	CONTINUE,
	BREAK,
	RETURN,

	// 状态关键字
	BEFORE,
	WHEN,
	AFTER,

	// 函数
	PRINT

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

	friend std::ostream& operator<<(std::ostream& os, const Token& token)
	{
		return os << "Token<" << static_cast<int>(token.type) << ", " << token.value << ">";
	}

};

#endif // !_TOKEN_H_
