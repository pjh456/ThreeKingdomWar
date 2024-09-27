#ifndef _AC_AUTOMATON_H_
#define _AC_AUTOMATON_H_

#include <string>
#include <vector>

#include "token.h"

/*
// ����ƥ��ʷ�������
class ACAutoMaton
{
public:
	ACAutoMaton() = default;
	~ACAutoMaton() = default;

	// ��ѯ������
	const TokenType find_key(const std::string input)
	{
		Node* current_node = this->get_node(input);
		return current_node ? current_node->get_type() : TokenType::ERROR;
	}

	// ���һ���µı�����
	void add_key(const std::string key, const TokenType type)
	{
		Node* current_node = this->get_node(key, true);	// �½�һ����ӳ��ڵ�
		current_node->set_type(type);	// ���ڵ������������ӳ��
	}

private:
	// �Զ����ڵ�
	struct Node
	{
	public:
		Node() = default;
		~Node() = default;

		Node(char ch, TokenType type):
			ch(ch), count(1), type(type) { }

		const int get_count() const
		{
			return count;
		}

		const TokenType get_type() const
		{
			return type;
		}
		
		void set_type(const TokenType type)
		{
			this->type = type;
		}

		Node* get_son_node(char ch) const
		{
			return nodes[ch];
		}

		// ���һ���½ڵ㣬��·���ϵĽڵ��ǲ����õģ������� ERROR ���
		Node* add_child(char ch, TokenType type = TokenType::ERROR)
		{
			if (!nodes[(int)ch])
			{
				nodes[(int)ch] = new Node(ch, type);
				count++;
			}
			return nodes[(int)ch];
		}

	private:
		char ch;							// �ڵ��ϵ��ַ�
		int count = 0;						// ��¼·���Ͻڵ����
		TokenType type = TokenType::ERROR;	// ��Ӧ��������
		Node* nodes[200] = { nullptr };		// �ӽڵ�

	};

	// ֱ�Ӳ��ҽڵ�ָ�룬��ѡ�Ƿ񴴽��½ڵ�
	Node* get_node(const std::string input, const bool create_new_node = false)
	{

		Node* current_node = nodes[0];
		for (int i = 0; i < input.size(); ++i)
		{
			if (current_node->get_son_node(input[i]))
				current_node = current_node->get_son_node(input[i]);
			else if (create_new_node)
				current_node = current_node->add_child(input[i]);
			else
				return nullptr;
		}
		return current_node;
	}

private:
	std::vector<Node*> nodes = std::vector<Node*>(1);

};

*/
#endif // !_AC_AUTOMATON_H_
