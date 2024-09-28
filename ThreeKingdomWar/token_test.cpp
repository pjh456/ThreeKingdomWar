
#include <iostream>

#include "token.h"

namespace Tests
{
	void test_token()
	{
		Token token1(TokenType::INT, "1");
		Token token2(TokenType::ASSIGN, "=");
		Token token3(TokenType::IDENTIFIER, "abc");
		std::cout << token1 << std::endl;
		std::cout << token2 << std::endl;
		std::cout << token3 << std::endl;
	}
}

/*
int main()
{
	Tests::test_token();
	return 0;
}
*/
