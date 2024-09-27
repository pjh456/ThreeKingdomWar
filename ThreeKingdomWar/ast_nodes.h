#ifndef _AST_NODES_H_
#define _AST_NODES_H_

#include <string>

#include "token.h"


// AST �ڵ�����
enum class ASTNodeType
{
	// ��ͨ����
	INTEGER,
	FLOAT,
	BOOL,
	VOID,
	FUNC,
	STRING,

	// ��������
	IDENTIFIER,			// ����
	BINARY_EXPRESSION,	// ��Ԫ���ʽ
	UNARY_EXPRESSION,	// һԪ���ʽ

	ASSIGNMENT,		// ����
	FUNCTION_CALL,	// ��������
	BLOCK			// �����

};

// AST�ڵ����
class ASTNode
{
public:
	virtual ~ASTNode() = default;
	virtual ASTNodeType get_type() const = 0;
};

// �����ڵ�
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

// �������ڵ�
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

// �ַ����ڵ�
class StringNode :public ASTNode
{
	StringNode(std::string value): value(value) {}
	ASTNodeType get_type() const override
	{
		return ASTNodeType::STRING;
	}
	std::string value;
};

// ����ֵ�ڵ�
class BooleanNode :public ASTNode
{
	BooleanNode(bool flag): flag(flag) {}
	ASTNodeType get_type() const override
	{
		return ASTNodeType::BOOL;
	}
	bool flag
};

// ������ʶ���ڵ�
class IdentifierNode :public ASTNode
{
	IdentifierNode();
	ASTNodeType get_type() const override
	{
		return ASTNodeType::IDENTIFIER;
	}
	// unfinished
};

// ��Ԫ���ʽ�ڵ�
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
