#ifndef _VARIABLE_MANAGER_H_
#define _VARIABLE_MANAGER_H_

#include <string>
#include <unordered_map>
#include <variant>

#include "token.h"
#include "ast_nodes.h"

class VariableTable
{
public:
	VariableTable() = default;
	~VariableTable() = default;

	void define(const std::string& name, ASTNode* value)
	{
		symbol_table[name] = new IdentifierNode(name, value);
	}

	void declare(const std::string& name, FunctionDeclarationNode* func)
	{
		function_table[name] = func;
	}

	IdentifierNode* get(const std::string& name)
	{
		return symbol_table[name];
	}

	void call(const std::string& name)
	{
		function_table[name]->call();
	}

private:
	std::unordered_map<std::string, IdentifierNode*> symbol_table;
	std::unordered_map<std::string, FunctionDeclarationNode*> function_table;
};

#endif // !_VARIABLE_MANAGER_H_
