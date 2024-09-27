#ifndef _LEXER_H_
#define _LEXER_H_

#include <string>
#include <vector>

#include "ac_automaton.h"
#include "token.h"

// �ʷ�������
class Lexer
{
public:
	~Lexer();

	Lexer(const std::string& text);

	Token get_next_token();

private:
	std::string input;

	size_t position				= 0;		// ��ǰλ��
	size_t read_position		= 0;		// ��ȡ����λ��

	char current_char			=' ';		// ��ǰ�ַ�
	ACAutoMaton* ac_automaton	= nullptr;	// AC�Զ���

	void read_char();
};

#endif // !_LEXER_H_
