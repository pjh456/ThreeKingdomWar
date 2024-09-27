#ifndef _AST_NODES_H_
#define _AST_NODES_H_

#include <string>

#include "token.h"


// AST 节点类型
enum class ASTNodeType
{
	// 普通类型
	INTEGER,
	FLOAT,
	BOOL,
	VOID,
	FUNC,
	STRING,

	// 抽象类型
	IDENTIFIER,			// 变量
	BINARY_EXPRESSION,	// 二元表达式
	UNARY_EXPRESSION,	// 一元表达式

	ASSIGNMENT,		// 声明
	FUNCTION_CALL,	// 函数调用
	BLOCK			// 代码块

};

// AST节点基类
class ASTNode
{
public:
	virtual ~ASTNode() = default;
	virtual ASTNodeType get_type() const = 0;
};

// 整数节点
class IntegerNode : public ASTNode
{
public:
	IntegerNode(int value): value(value){}
	ASTNodeType get_type() const override
	{
		return ASTNodeType::INTEGER;
	}
	int value;
};

// 浮点数节点
class FloatNode : public ASTNode
{
public:
	FloatNode(float value): value(value){}
	ASTNodeType get_type() const override
	{
		return ASTNodeType::FLOAT;
	}
	float value;
};

// 字符串节点
class StringNode :public ASTNode
{
	StringNode(std::string value): value(value) {}
	ASTNodeType get_type() const override
	{
		return ASTNodeType::STRING;
	}
	std::string value;
};

// 布尔值节点
class BooleanNode :public ASTNode
{
	BooleanNode(bool flag): flag(flag) {}
	ASTNodeType get_type() const override
	{
		return ASTNodeType::BOOL;
	}
	bool flag
};

// 变量标识符节点
class IdentifierNode :public ASTNode
{
	IdentifierNode();
	ASTNodeType get_type() const override
	{
		return ASTNodeType::IDENTIFIER;
	}
	// unfinished
};

// 二元表达式节点
class BinaryExpressionNode : public ASTNode
{
public:
	BinaryExpressionNode(ASTNode* left, TokenType op, ASTNode* right) :
		left(left), op(op), right(right) {}
	ASTNodeType get_type() const override
	{
		return ASTNodeType::BINARY_EXPRESSION;
	}
	ASTNode* left;
	TokenType op;
	ASTNode* right;
};


#endif // !_AST_NODES_H_
