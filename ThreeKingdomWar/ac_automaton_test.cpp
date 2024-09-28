
#include <iostream>

#include "ac_automaton.h"

namespace Tests
{
	void test_ac_automaton()
	{
		ACAutoMaton ac;
		ac.add_key("111", TokenType::INT);
		ac.add_key("false", TokenType::BOOL);
		ac.add_key("func", TokenType::FUNC);
		ac.add_key("+", TokenType::PLUS);
		std::cout << "Add key finished!\n";

		std::cout << static_cast<int>(ac.find_key("111")) << static_cast<int>(TokenType::INT) << std::endl;
		std::cout << static_cast<int>(ac.find_key("false")) << static_cast<int>(TokenType::BOOL) << std::endl;
		std::cout << static_cast<int>(ac.find_key("func")) << static_cast<int>(TokenType::FUNC) << std::endl;
		std::cout << static_cast<int>(ac.find_key("+")) << static_cast<int>(TokenType::PLUS) << std::endl;
	}
}

/*
int main()
{
	Tests::test_ac_automaton();
	return 0;
}
*/

