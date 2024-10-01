#include "ast_nodes.h"

// BlockNode

ASTNodeType BlockNode::get_type() const
{
	return ASTNodeType::BLOCK;
}

const std::vector<ASTNode*>& BlockNode::get_statements() const
{
	return statements;
}

void BlockNode::define(const std::string& name, ASTNode* value)
{
	symbol_table[name] = new IdentifierNode(name, value);
}

void BlockNode::declare(const std::string& name, ASTNode* func)
{
	if (auto func_declared = dynamic_cast<FunctionDeclarationNode*>(func))
		function_table[name] = func_declared;
	else
		throw std::invalid_argument("Invalid ASTNode type for function declaration");
}

IdentifierNode* BlockNode::get(const std::string& name)
{
	return symbol_table[name];
}

void BlockNode::call(const std::string& name)
{
	if (auto function_called = dynamic_cast<FunctionDeclarationNode*>(function_table[name]))
		function_called->call();
}

// IntegerNode

ASTNodeType IntegerNode::get_type() const
{
	return ASTNodeType::INTEGER;
}

int IntegerNode::get_value() const
{
	return value;
}

std::ostream& operator<<(std::ostream& os, const IntegerNode& node)
{
	return os << "IntegerNode<" << node.value << ">";
}

// FloatNode

ASTNodeType FloatNode::get_type() const
{
	return ASTNodeType::FLOAT;
}

float FloatNode::get_value() const
{
	return value;
}

std::ostream& operator<<(std::ostream& os, const FloatNode& node)
{
	return os << "FloatNode<" << node.value << ">";
}

// StringNode

ASTNodeType StringNode::get_type() const
{
	return ASTNodeType::STRING;
}

const std::string& StringNode::get_value() const
{
	return value;
}

std::ostream& operator<<(std::ostream& os, const StringNode& node)
{
	return os << "StringNode<" << node.value << ">";
}

// BooleanNode

ASTNodeType BooleanNode::get_type() const
{
	return ASTNodeType::BOOL;
}

bool BooleanNode::get_value() const
{
	return value;
}

std::ostream& operator<<(std::ostream& os, const BooleanNode& node)
{
	return os << "BooleanNode<" << node.value << ">";
}

// ListNode

ASTNodeType ListNode::get_type() const
{
	return ASTNodeType::LIST;
}

const std::vector<ASTNode*>& ListNode::get_elements() const
{
	return elements;
}

std::ostream& operator<<(std::ostream& os, const ListNode& node)
{
	return os << "ListNode<" << ">";
}

// IdentifierNode

ASTNodeType IdentifierNode::get_type() const
{
	return ASTNodeType::IDENTIFIER;
}

const std::string& IdentifierNode::get_name() const
{
	return name;
}

const ASTNode* IdentifierNode::get_value() const
{
	return value;
}

std::ostream& operator<<(std::ostream& os, const IdentifierNode& node)
{
	return os << "IdentifierNode<" << node.name << ", " << static_cast<int>(node.value->get_type()) << ">";
}

// BinaryExpressionNode

ASTNodeType BinaryExpressionNode::get_type() const
{
	return ASTNodeType::BINARY_EXPRESSION;
}

ASTNode* BinaryExpressionNode::get_left() const
{
	return left;
}

Token BinaryExpressionNode::get_operator() const
{
	return op;
}

ASTNode* BinaryExpressionNode::get_right() const
{
	return right;
}

// UnaryExpressionNode

ASTNodeType UnaryExpressionNode::get_type() const
{
	return ASTNodeType::UNARY_EXPRESSION;
}

TokenType UnaryExpressionNode::get_operator() const
{
	return op;
}

ASTNode* UnaryExpressionNode::get_expression() const
{
	return expression;
}

// AssignmentNode

ASTNodeType AssignmentNode::get_type() const
{
	return ASTNodeType::ASSIGNMENT;
}

IdentifierNode* AssignmentNode::get_identifier() const
{
	return identifier;
}

ASTNode* AssignmentNode::get_value() const
{
	return value;
}

// IfStatementNode

ASTNodeType IfStatementNode::get_type() const
{
	return ASTNodeType::IF_STATEMENT;
}

ASTNode* IfStatementNode::get_condition() const
{
	return condition;
}

BlockNode* IfStatementNode::get_then_block() const
{
	return then_block;
}

BlockNode* IfStatementNode::get_else_block() const
{
	return else_block;
}

// WhileStatementNode

ASTNodeType WhileStatementNode::get_type() const
{
	return ASTNodeType::WHILE_STATEMENT;
}

ASTNode* WhileStatementNode::get_condition() const
{
	return condition;
}

BlockNode* WhileStatementNode::get_block() const
{
	return block;
}

// ForStatementNode

ASTNodeType ForStatementNode::get_type() const
{
	return ASTNodeType::FOR_STATEMENT;
}

IdentifierNode* ForStatementNode::get_object() const
{
	return object;
}

ListNode* ForStatementNode::get_objects() const
{
	return objects;
}

BlockNode* ForStatementNode::get_block() const
{
	return block;
}

// FunctionDeclarationNode

ASTNodeType FunctionDeclarationNode::get_type() const
{
	return ASTNodeType::FUNCTION_DECLARATION;
}

const std::string& FunctionDeclarationNode::get_name() const
{
	return name;
}

const std::vector<IdentifierNode*>& FunctionDeclarationNode::get_parameters() const
{
	return parameters;
}

BlockNode* FunctionDeclarationNode::get_body() const
{
	return body;
}

void FunctionDeclarationNode::call()
{

}

std::ostream& operator<<(std::ostream& os, const FunctionDeclarationNode& node)
{
	return os << "Declare function: " << node.name << "(..)";
}

// FunctionCallNode

ASTNodeType FunctionCallNode::get_type() const
{
	return ASTNodeType::FUNCTION_CALL;
}

const std::string& FunctionCallNode::get_name() const
{
	return name;
}

const std::vector<ASTNode*>& FunctionCallNode::get_arguments() const
{
	return arguments;
}

std::ostream& operator<<(std::ostream& os, const FunctionCallNode& node)
{
	return os << "Call function: " << node.name << "(..)";
}

// ContinueStatementNode

ASTNodeType ContinueStatementNode::get_type() const
{
	return ASTNodeType::CONTINUE_STATEMENT;
}

// BreakStatementNode

ASTNodeType BreakStatementNode::get_type() const
{
	return ASTNodeType::BREAK_STATEMENT;
}

// ReturnStatementNode

ASTNodeType ReturnStatementNode::get_type() const
{
	return ASTNodeType::RETURN_STATEMENT;
}
