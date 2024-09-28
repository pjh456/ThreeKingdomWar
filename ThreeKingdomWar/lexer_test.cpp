
#include <iostream>
#include <string>
#include "lexer.h"

namespace Tests
{
    void test_lexer(const std::string& input) {
        Lexer lexer(input);
        Token token(TokenType::UNKNOWN, " ");
        do {
            token = lexer.get_next_token();
            std::cout << "Token: " << static_cast<int>(token.type) << ", Value: " << token.value << std::endl;
        } while (token.type != TokenType::UNKNOWN); // Assuming UNKNOWN indicates end
    }

    void test_lexers()
    {
        std::cout << "Testing identifiers and keywords:\n";
        test_lexer("int myVar; float number; Func myFunc;");

        std::cout << "\nTesting numbers:\n";
        test_lexer("42 100 3.14");

        std::cout << "\nTesting operators:\n";
        test_lexer("a + b - c * d / e;");

        std::cout << "\nTesting strings:\n";
        test_lexer("\"Hello, World!\" 'Single quotes'");

        std::cout << "\nTesting comments:\n";
        test_lexer("# This is a comment\nint validVar; # Another comment");

        std::cout << "\nTesting mixed input:\n";
        test_lexer("Func testFunc() { int x = 5; } # This is a comment");

    }
}

/*
int main()
{
    Tests::test_lexers();
    return 0;
}
*/

