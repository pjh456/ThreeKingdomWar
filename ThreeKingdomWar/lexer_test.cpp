

#include <iostream>
#include "string"

#include "lexer.h"


int main()
{
	Lexer lexer1 = Lexer("WOaas");
	Lexer lexer2 = Lexer("7142");
	Lexer lexer3 = Lexer("1 +");
	Lexer lexer4 = Lexer("aaaa");

	std::cout << lexer1.get_next_token() << std::endl;
	std::cout << lexer2.get_next_token() << std::endl;
	std::cout << lexer3.get_next_token() << std::endl;
	std::cout << lexer3.get_next_token() << std::endl;
	std::cout << lexer4.get_next_token() << std::endl;
	return 0;
}

