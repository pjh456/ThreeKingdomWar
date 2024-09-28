#ifndef _VARIABLE_MANAGER_H_
#define _VARIABLE_MANAGER_H_

#include <string>
#include <unordered_map>
#include <variant>

#include "token.h"

class VariableManager
{
public:
	VariableManager() = default;
	~VariableManager() = default;

	void add_variable(const TokenType type, const std::string& name);

private:
	std::unordered_map<std::string, int> int_variable_pool;
	std::unordered_map<std::string, float> float_variable_pool;
	std::unordered_map<std::string, bool> bool_variable_pool;
	std::unordered_map<std::string, void> void_variable_pool;
};

#endif // !_VARIABLE_MANAGER_H_
