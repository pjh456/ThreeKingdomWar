
#include <iostream>
#include "lexer.h"
#include "parser.h"

namespace Tests
{
    void test_parser() {
        std::string input;

        // 测试函数声明和调用
        input = "Func add() { return; }";
        Lexer lexer1(input);
        Parser parser1(lexer1);
        try {
            parser1.parse();
            std::cout << "Function declaration and call parsing successful!\n";
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // 测试变量声明和赋值
        input = "Int x = 10; Int y = 20; x = x + y;";
        Lexer lexer2(input);
        Parser parser2(lexer2);
        try {
            parser2.parse();
            std::cout << "Variable declaration and assignment parsing successful!\n";
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // 测试控制流语句
        input = "while (true) { if (condition) { continue; } break; }";
        Lexer lexer3(input);
        Parser parser3(lexer3);
        try {
            parser3.parse();
            std::cout << "Control flow statements parsing successful!\n";
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // 测试 for 循环
        input = "for (i: objects) { x = i; }";
        Lexer lexer4(input);
        Parser parser4(lexer4);
        try {
            parser4.parse();
            std::cout << "For loop parsing successful!\n";
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // 测试代码块
        input = "{ Int z = x + y; return; }";
        Lexer lexer5(input);
        Parser parser5(lexer5);
        try {
            parser5.parse();
            std::cout << "Code block parsing successful!\n";
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}


int main() {
    Tests::test_parser();
    return 0;
}

