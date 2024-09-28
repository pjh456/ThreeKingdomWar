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

	void add_variable(IdentifierNode* variable)
	{
		variable_pool[variable->get_name()] = variable;
	}

	IdentifierNode* get_variable(const std::string& name)
	{
		return variable_pool[name];
	}

private:
	std::unordered_map<std::string, IdentifierNode*> variable_pool;
};

#endif // !_VARIABLE_MANAGER_H_
