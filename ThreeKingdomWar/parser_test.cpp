#include <iostream>
#include "lexer.h"
#include "parser.h"

int main() {
    // ���Ա��ʽ
    std::vector<std::string> test_expressions = {
        "3 + 5;",
        "10 - 2 * 3;",
        "(1 + 2) * 4;",
        "8 / 2 + 3;",
        "7 * (3 + 2);"
    };

    for (const auto& expr : test_expressions) {
        std::cout << "Testing expression: " << expr << std::endl;
        Lexer lexer(expr);
        Parser parser(lexer);
        try {
            parser.parse(); // ������������ʽ
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
