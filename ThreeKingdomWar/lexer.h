#ifndef _LEXER_H_
#define _LEXER_H_

#include <string>
#include <vector>

#include "ac_automaton.h"
#include "token.h"

// 词法分析器
class Lexer
{
public:
	~Lexer();

	Lexer(const std::string& text);

	Token get_next_token();

private:
	std::string input;

	size_t position				= 0;		// 当前位置
	size_t read_position		= 0;		// 读取到的位置

	char current_char			=' ';		// 当前字符
	ACAutoMaton* ac_automaton	= nullptr;	// AC自动机

	void read_char();
};

#endif // !_LEXER_H_
