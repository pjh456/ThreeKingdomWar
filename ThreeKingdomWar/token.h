#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <iostream>

enum class TokenType
{
	ERROR,
	// 运算符
	PLUS,	// +
	MINUS,	// -
	MUL,	// *
	DIV,	// /
	ASSIGN,	// =

	// 标识符
	LPAREN,	// (
	RPAREN, // )
	SEMICOLON,	// ;

	// 变量类型
	INT,	// 整数
	FLOAT,	// 浮点数
	BOOL,	// 布尔值
	VOID,	// 空值
	FUNC,	// 函数
	
	// 抽象定义
	IDENTIFIER,	// 变量
	ITERGER,	// 数字
	EOF_TOKEN,	// 结束标记


};

// 语义标记
class Token
{
public:
	TokenType type;
	std::string value;
	Token(TokenType type, std::string value) : 
		type(type), value(value) { }

	friend std::ostream& operator<<(std::ostream& os, const Token& token);

};
#endif // !_TOKEN_H_
