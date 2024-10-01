#ifndef _AST_NODES_H_
#define _AST_NODES_H_

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

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
// 整数节点
class IntegerNode : public ASTNode
{
public:
	IntegerNode(int value): value(value){}

	ASTNodeType get_type() const override;

	int get_value() const;

	friend std::ostream& operator<<(std::ostream& os, const IntegerNode& node);

private:
	int value;
};

// 浮点数节点
class FloatNode : public ASTNode
{
public:
	FloatNode(float value): value(value){}

	ASTNodeType get_type() const override;

	float get_value() const;

	friend std::ostream& operator<<(std::ostream& os, const FloatNode& node);

private:
	float value;
};

// 字符串节点
class StringNode :public ASTNode
{
public:
	StringNode(std::string value): value(value) {}

	ASTNodeType get_type() const override;

	const std::string& get_value() const;

	friend std::ostream& operator<<(std::ostream& os, const StringNode& node);

private:
	std::string value;
};

// 布尔值节点
class BooleanNode :public ASTNode
{
public:
	BooleanNode(bool value): value(value) {}

	ASTNodeType get_type() const override;

	bool get_value() const;

	friend std::ostream& operator<<(std::ostream& os, const BooleanNode& node);

private:
	bool value;
};

// 列表节点
class ListNode :public ASTNode
{
public:
	ListNode(const std::vector<ASTNode*>& elements) : elements(elements) {}

	ASTNodeType get_type() const override;

	const std::vector<ASTNode*>& get_elements() const;

	friend std::ostream& operator<<(std::ostream& os, const ListNode& node);

private:
	std::vector<ASTNode*> elements; // 存储元素的 AST 节点

};

// 变量标识符节点（整合其他基本类型）
class IdentifierNode :public ASTNode
{
public:
	IdentifierNode(const std::string& name) :
		name(name), value(nullptr) {}

	IdentifierNode(const std::string& name, ASTNode* value): 
		name(name), value(value) {}

	ASTNodeType get_type() const override;

	const std::string& get_name() const;

	const ASTNode* get_value() const;

	friend std::ostream& operator<<(std::ostream& os, const IdentifierNode& node);

private:
	std::string name;
	ASTNode* value;
};

// 代码块节点
class BlockNode : public ASTNode
{
public:
	BlockNode(const std::vector<ASTNode*>& statements) : statements(statements) {}

	ASTNodeType get_type() const override;

	const std::vector<ASTNode*>& get_statements() const;

	void define(const std::string& name, ASTNode* value);

	void declare(const std::string& name, ASTNode* func);

	IdentifierNode* get(const std::string& name);

	void call(const std::string& name);

private:
	std::vector<ASTNode*> statements; // 存储多个语句

	std::unordered_map<std::string, IdentifierNode*> symbol_table;
	std::unordered_map<std::string, ASTNode*> function_table;//不能用FunctionDeclarationNode，不然会循环依赖

};


// 二元表达式节点
class BinaryExpressionNode : public ASTNode
{
public:
	BinaryExpressionNode(ASTNode* left, Token op, ASTNode* right) :
		left(left), op(op), right(right) {}

	ASTNodeType get_type() const override;

	ASTNode* get_left() const;

	Token get_operator() const;

	ASTNode* get_right() const;

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

	ASTNodeType get_type() const override;

	TokenType get_operator() const;

	ASTNode* get_expression() const;
	
private:
	TokenType op;
	ASTNode* expression;
};

// 赋值节点
class AssignmentNode : public ASTNode {
public:
	AssignmentNode(IdentifierNode* identifier, ASTNode* value)
		: identifier(identifier), value(value) {}

	ASTNodeType get_type() const override;

	IdentifierNode* get_identifier() const;

	ASTNode* get_value() const;

private:
	IdentifierNode* identifier;
	ASTNode* value;
};

// 条件节点
class IfStatementNode : public ASTNode {
public:
	IfStatementNode(ASTNode* condition, BlockNode* then_block, BlockNode* else_block = nullptr)
		: condition(condition), then_block(then_block), else_block(else_block) {}

	ASTNodeType get_type() const override;

	ASTNode* get_condition() const;

	BlockNode* get_then_block() const;

	BlockNode* get_else_block() const;

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

	ASTNodeType get_type() const override;

	ASTNode* get_condition() const;

	BlockNode* get_block() const;

private:
	ASTNode* condition;
	BlockNode* block;
};

// 循环节点
class ForStatementNode : public ASTNode
{
public:
	ForStatementNode(IdentifierNode* object, ListNode* objects, BlockNode* block)
		: object(object), objects(objects), block(block) {}

	ASTNodeType get_type() const override;

	IdentifierNode* get_object() const;

	ListNode* get_objects() const;

	BlockNode* get_block() const;

private:
	IdentifierNode* object;
	ListNode* objects;
	BlockNode* block;
};

// 函数声明节点
class FunctionDeclarationNode : public ASTNode {
public:
	FunctionDeclarationNode(const std::string& name, const std::vector<IdentifierNode*>& parameters, BlockNode* body)
		: name(name), parameters(parameters), body(body) {}

	ASTNodeType get_type() const override;

	const std::string& get_name() const;

	const std::vector<IdentifierNode*>& get_parameters() const;

	BlockNode* get_body() const;

	void call();

	friend std::ostream& operator<<(std::ostream& os, const FunctionDeclarationNode& node);

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

	ASTNodeType get_type() const override;

	const std::string& get_name() const;

	const std::vector<ASTNode*>& get_arguments() const;

	friend std::ostream& operator<<(std::ostream& os, const FunctionCallNode& node);

private:
	std::string name;
	std::vector<ASTNode*> arguments;
};

// continue语句节点
class ContinueStatementNode : public ASTNode 
{
public:
	ASTNodeType get_type() const override;

};

// break语句节点
class BreakStatementNode : public ASTNode 
{
public:
	ASTNodeType get_type() const override;

};

// return语句节点
class ReturnStatementNode : public ASTNode 
{
public:
	//ReturnStatementNode(ASTNode* value = nullptr) : value(value) {}

	ASTNodeType get_type() const override;

//private:
	//暂时不考虑返回值部分
	//ASTNode* value; // 可以是返回值，也可以是空（无返回值）
};




#endif // !_AST_NODES_H_
