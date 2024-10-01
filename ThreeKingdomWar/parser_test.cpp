
#include <iostream>
#include "lexer.h"
#include "parser.h"

namespace Tests
{
    void test_parser(const std::string& input) {
        Lexer lexer(input);
        Parser parser(lexer);

        try {
            ASTNode* ast = parser.parse();
            // 这里可以添加对AST的遍历或打印函数，以验证AST结构
            std::cout << "Parsing successful!" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Parsing error: \n" << e.what() << std::endl;
        }
    }

    void test_parsers()
    {
        std::string input = R"(
            Func main() {
                Int x = 10;
                Float y = 3.14;
                Bool z = True;
                String name = "ChatGPT";

                if (x < y) {
                    x = x + 1;
                } else {
                    z = False;
                }

                while (z) {
                    z = False;
                }

                for (i:myList) {
                    i = i + 1;
                }

                return;
            }
        )";

        test_parser(input);
    }
}


int main() {
    Tests::test_parsers();
    return 0;
}

