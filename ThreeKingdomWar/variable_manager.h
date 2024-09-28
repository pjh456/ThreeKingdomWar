#ifndef _VARIABLE_MANAGER_H_
#define _VARIABLE_MANAGER_H_

#include <string>
#include <unordered_map>
#include <variant>

#include "token.h"
#include "ast_nodes.h"

class VariableManager
{
public:
	VariableManager() = default;
	~VariableManager() = default;

	void define(const std::string& name, ASTNode* value)
	{
		variable_pool[name] = new IdentifierNode(name, value);
	}

	IdentifierNode* get(const std::string& name)
	{
		return variable_pool[name];
	}

private:
	std::unordered_map<std::string, IdentifierNode*> variable_pool;
};

#endif // !_VARIABLE_MANAGER_H_
