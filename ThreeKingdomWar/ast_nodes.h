#ifndef _AST_NODES_H_
#define _AST_NODES_H_

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

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
	LIST,

	// �߼�����
	PLAYER,
	STATE,
	CARD,
	CARD_CONTAINER,

	// ��������
	IDENTIFIER,			// ����
	BINARY_EXPRESSION,	// ��Ԫ���ʽ
	UNARY_EXPRESSION,	// һԪ���ʽ

	ASSIGNMENT,		// ��ֵ
	BLOCK,			// �����

	// ����
	FUNCTION_DECLARATION,	// ��������
	FUNCTION_CALL,			// ��������

	//�ؼ���
	IF_STATEMENT,		// �������
	WHILE_STATEMENT,	// ѭ�����
	FOR_STATEMENT,
	CONTINUE_STATEMENT,
	BREAK_STATEMENT,
	RETURN_STATEMENT

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

	ASTNodeType get_type() const override;

	int get_value() const;

	friend std::ostream& operator<<(std::ostream& os, const IntegerNode& node);

private:
	int value;
};

// �������ڵ�
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

// �ַ����ڵ�
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

// ����ֵ�ڵ�
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

// �б�ڵ�
class ListNode :public ASTNode
{
public:
	ListNode(const std::vector<ASTNode*>& elements) : elements(elements) {}

	ASTNodeType get_type() const override;

	const std::vector<ASTNode*>& get_elements() const;

	friend std::ostream& operator<<(std::ostream& os, const ListNode& node);

private:
	std::vector<ASTNode*> elements; // �洢Ԫ�ص� AST �ڵ�

};

// ������ʶ���ڵ㣨���������������ͣ�
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

// �����ڵ�
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
	std::vector<ASTNode*> statements; // �洢������

	std::unordered_map<std::string, IdentifierNode*> symbol_table;
	std::unordered_map<std::string, ASTNode*> function_table;//������FunctionDeclarationNode����Ȼ��ѭ������

};


// ��Ԫ���ʽ�ڵ�
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

// һԪ���ʽ�ڵ�
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

// ��ֵ�ڵ�
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

// �����ڵ�
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

// ѭ���ڵ�
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

// ѭ���ڵ�
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

// ���������ڵ�
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

// �������ýڵ�
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

// continue���ڵ�
class ContinueStatementNode : public ASTNode 
{
public:
	ASTNodeType get_type() const override;

};

// break���ڵ�
class BreakStatementNode : public ASTNode 
{
public:
	ASTNodeType get_type() const override;

};

// return���ڵ�
class ReturnStatementNode : public ASTNode 
{
public:
	//ReturnStatementNode(ASTNode* value = nullptr) : value(value) {}

	ASTNodeType get_type() const override;

//private:
	//��ʱ�����Ƿ���ֵ����
	//ASTNode* value; // �����Ƿ���ֵ��Ҳ�����ǿգ��޷���ֵ��
};




#endif // !_AST_NODES_H_
