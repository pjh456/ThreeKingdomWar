#ifndef _AST_NODES_H_
#define _AST_NODES_H_

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

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
	LIST,

	// 高级类型
	PLAYER,
	STATE,
	CARD,
	CARD_CONTAINER,

	// 抽象类型
	IDENTIFIER,			// 变量
	BINARY_EXPRESSION,	// 二元表达式
	UNARY_EXPRESSION,	// 一元表达式

	ASSIGNMENT,		// 赋值
	BLOCK,			// 代码块

	// 函数
	FUNCTION_DECLARATION,	// 函数声明
	FUNCTION_CALL,			// 函数调用

	//关键字
	IF_STATEMENT,		// 条件语句
	WHILE_STATEMENT,	// 循环语句
	FOR_STATEMENT,
	CONTINUE_STATEMENT,
	BREAK_STATEMENT,
	RETURN_STATEMENT

};

// AST节点基类
class ASTNode
{
public:
	virtual ~ASTNode() = default;
	virtual ASTNodeType get_type() const = 0;
	
};

// 代码块节点
class BlockNode : public ASTNode 
{
public:
	BlockNode(const std::vector<ASTNode*>& statements) : statements(statements) {}

	ASTNodeType get_type() const override 
	{
		return ASTNodeType::BLOCK;
	}

	const std::vector<ASTNode*>& get_statements() const 
	{
		return statements;
	}

private:
	std::vector<ASTNode*> statements; // 存储多个语句
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

	int get_value() const
	{
		return value;
	}

	friend std::ostream& operator<<(std::ostream& os, const IntegerNode& node)
	{
		return os << "IntegerNode<" << node.value << ">";
	}

private:
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

	float get_value() const
	{
		return value;
	}

	friend std::ostream& operator<<(std::ostream& os, const FloatNode& node)
	{
		return os << "FloatNode<" << node.value << ">";
	}

private:
	float value;
};

// 字符串节点
class StringNode :public ASTNode
{
public:
	StringNode(std::string value): value(value) {}

	ASTNodeType get_type() const override
	{
		return ASTNodeType::STRING;
	}

	const std::string& get_value() const
	{
		return value;
	}


	friend std::ostream& operator<<(std::ostream& os, const StringNode& node)
	{
		return os << "StringNode<" << node.value << ">";
	}

private:
	std::string value;
};

// 布尔值节点
class BooleanNode :public ASTNode
{
public:
	BooleanNode(bool value): value(value) {}

	ASTNodeType get_type() const override
	{
		return ASTNodeType::BOOL;
	}

	bool get_value() const
	{
		return value;
	}

	friend std::ostream& operator<<(std::ostream& os, const BooleanNode& node)
	{
		return os << "BooleanNode<" << node.value << ">";
	}

private:
	bool value;
};

class NumberNode: public ASTNode
{
public:
	NumberNode(const IntegerNode* value) :
		value((float)value->get_value()) {}
	NumberNode(const FloatNode* value) :
		value(value->get_value()) {}
	NumberNode(const BooleanNode* value) :
		value((float)value->get_value()) {}

	
private:
	float value;
};

// 列表节点
class ListNode :public ASTNode
{
public:
	ListNode(const std::vector<ASTNode*>& elements) : elements(elements) {}

	ASTNodeType get_type() const override
	{
		return ASTNodeType::LIST;
	}

	const std::vector<ASTNode*>& get_elements() const
	{
		return elements;
	}

private:
	std::vector<ASTNode*> elements; // 存储元素的 AST 节点

};

// 变量标识符节点（整合其他基本类型）
class IdentifierNode :public ASTNode
{
public:
	IdentifierNode(const std::string& name) :
		name(name) {}
	IdentifierNode(const std::string& name, ASTNode* value): 
		name(name), value(value) {}

	ASTNodeType get_type() const override
	{
		return ASTNodeType::IDENTIFIER;
	}

	const std::string& get_name() const
	{
		return name;
	}

	const ASTNode* get_value() const
	{
		return value;
	}

	friend std::ostream& operator<<(std::ostream& os, const IdentifierNode& node)
	{
		return os << "IdentifierNode<" << node.name << ", " << static_cast<int>(node.value->get_type()) << ">";
	}


private:
	std::string name;
	ASTNode* value;
};

// 二元表达式节点
class BinaryExpressionNode : public ASTNode
{
public:
	BinaryExpressionNode(ASTNode* left, Token op, ASTNode* right) :
		left(left), op(op), right(right) {}

	ASTNodeType get_type() const override
	{
		return ASTNodeType::BINARY_EXPRESSION;
	}

	ASTNode* get_left() const
	{
		return left;
	}

	Token get_operator() const
	{
		return op;
	}

	ASTNode* get_right() const
	{
		return right;
	}

private:
	ASTNode* left;
	Token op;
	ASTNode* right;
};

// 一元表达式节点
class UnaryExpressionNode :public ASTNode
{
public:
	UnaryExpressionNode(TokenType op, ASTNode* expression):
		op(op), expression(expression) {}

	ASTNodeType get_type() const override
	{
		return ASTNodeType::UNARY_EXPRESSION;
	}

	TokenType get_operator() const
	{
		return op;
	}

	ASTNode* get_expression() const
	{
		return expression;
	}
	
private:
	TokenType op;
	ASTNode* expression;
};

// 赋值节点
class AssignmentNode : public ASTNode {
public:
	AssignmentNode(IdentifierNode* identifier, ASTNode* value)
		: identifier(identifier), value(value) {}

	ASTNodeType get_type() const override
	{
		return ASTNodeType::ASSIGNMENT;
	}

	IdentifierNode* get_identifier() const 
	{
		return identifier;
	}

	ASTNode* get_value() const 
	{
		return value;
	}

private:
	IdentifierNode* identifier;
	ASTNode* value;
};

// 条件节点
class IfStatementNode : public ASTNode {
public:
	IfStatementNode(ASTNode* condition, BlockNode* then_block, BlockNode* else_block = nullptr)
		: condition(condition), then_block(then_block), else_block(else_block) {}

	ASTNodeType get_type() const override 
	{
		return ASTNodeType::IF_STATEMENT;
	}

	ASTNode* get_condition() const 
	{
		return condition;
	}

	BlockNode* get_then_block() const 
	{
		return then_block;
	}

	BlockNode* get_else_block() const 
	{
		return else_block;
	}

private:
	ASTNode* condition;
	BlockNode* then_block;
	BlockNode* else_block;
};

// 循环节点
class WhileStatementNode : public ASTNode 
{
public:
	WhileStatementNode(ASTNode* condition, BlockNode* block)
		: condition(condition), block(block) {}

	ASTNodeType get_type() const override 
	{
		return ASTNodeType::WHILE_STATEMENT;
	}

	ASTNode* get_condition() const 
	{
		return condition;
	}

	BlockNode* get_block() const 
	{
		return block;
	}

private:
	ASTNode* condition;
	BlockNode* block;
};

// 循环节点
class ForStatementNode : public ASTNode
{
public:
	ForStatementNode(IdentifierNode* object, IdentifierNode* objects, BlockNode* block)
		: object(object), objects(objects), block(block) {}

	ASTNodeType get_type() const override
	{
		return ASTNodeType::FOR_STATEMENT;
	}

	IdentifierNode* get_object() const
	{
		return object;
	}

	ASTNode* get_objects() const
	{
		return objects;
	}

	BlockNode* get_block() const
	{
		return block;
	}

private:
	IdentifierNode* object;
	IdentifierNode* objects;
	BlockNode* block;
};

// 函数声明节点
class FunctionDeclarationNode : public ASTNode {
public:
	FunctionDeclarationNode(const std::string& name, const std::vector<IdentifierNode*>& parameters, BlockNode* body)
		: name(name), parameters(parameters), body(body) {}

	ASTNodeType get_type() const override 
	{
		return ASTNodeType::FUNCTION_DECLARATION;
	}

	const std::string& get_name() const 
	{
		return name;
	}

	const std::vector<IdentifierNode*>& get_parameters() const 
	{
		return parameters;
	}

	BlockNode* get_body() const 
	{
		return body;
	}

	void call();

private:
	std::string name;
	std::vector<IdentifierNode*> parameters;
	BlockNode* body;
};

// 函数调用节点
class FunctionCallNode : public ASTNode 
{
public:
	FunctionCallNode(const std::string& name, const std::vector<ASTNode*>& arguments)
		: name(name), arguments(arguments) {}

	ASTNodeType get_type() const override 
	{
		return ASTNodeType::FUNCTION_CALL;
	}

	const std::string& get_name() const 
	{
		return name;
	}

	const std::vector<ASTNode*>& get_arguments() const 
	{
		return arguments;
	}


private:
	std::string name;
	std::vector<ASTNode*> arguments;
};

// continue语句节点
class ContinueStatementNode : public ASTNode 
{
public:
	ASTNodeType get_type() const override 
	{
		return ASTNodeType::CONTINUE_STATEMENT;
	}
};

// break语句节点
class BreakStatementNode : public ASTNode 
{
public:
	ASTNodeType get_type() const override 
	{
		return ASTNodeType::BREAK_STATEMENT;
	}
};

// return语句节点
class ReturnStatementNode : public ASTNode 
{
public:
	//ReturnStatementNode(ASTNode* value = nullptr) : value(value) {}

	ASTNodeType get_type() const override 
	{
		return ASTNodeType::RETURN_STATEMENT;
	}

//private:
	//暂时不考虑返回值部分
	//ASTNode* value; // 可以是返回值，也可以是空（无返回值）
};




#endif // !_AST_NODES_H_
