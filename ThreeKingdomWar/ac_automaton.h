#ifndef _AC_AUTOMATON_H_
#define _AC_AUTOMATON_H_

#include <string>
#include <vector>

#include "token.h"


// ����ƥ��ʷ�������
class ACAutoMaton
{
public:
	ACAutoMaton()
	{
		Node* root = new Node(this, ' ', TokenType::UNKNOWN);
		nodes.push_back(root);
	}
	~ACAutoMaton()
	{
		for (auto node : nodes)
			delete node;
		return;
	}

	// ��ѯ������
	const TokenType find_key(const std::string input)
	{
		Node* current_node = this->get_node(input);
		return current_node ? current_node->get_type() : TokenType::UNKNOWN;
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

		Node(ACAutoMaton* parent, char ch, TokenType type) :
			parent(parent), ch(ch), count(1), type(type) { }

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
			return nodes[(int)ch];
		}

		// ���һ���½ڵ㣬��·���ϵĽڵ��ǲ����õģ������� UNKNOWN ���
		Node* add_child(char ch, TokenType type = TokenType::UNKNOWN)
		{
			if (!nodes[(int)ch])
			{
				parent->nodes.push_back(nodes[(int)ch] = new Node(parent, ch, type));
				count++;
			}
			return nodes[(int)ch];
		}

	private:
		ACAutoMaton* parent;				// ����AC�Զ���
		char ch;							// �ڵ��ϵ��ַ�
		int count = 0;						// ��¼·���Ͻڵ����
		TokenType type = TokenType::UNKNOWN;	// ��Ӧ��������
		Node* nodes[256] = { nullptr };		// �ӽڵ�

	};

	// ֱ�Ӳ��ҽڵ�ָ�룬��ѡ�Ƿ񴴽��½ڵ�
	Node* get_node(const std::string input, const bool create_new_node = false)
	{

		Node* current_node = nodes[0];
		for (int i = 0; i < input.size(); ++i)
		{
			Node* son = current_node->get_son_node(input[i]);
			if (!son)
			{
				if (create_new_node)
					son = current_node->add_child(input[i]);
				else
					return nullptr;
			}
			current_node = son;
		}
		return current_node;
	}

private:
	std::vector<Node*> nodes;

};


#endif // !_AC_AUTOMATON_H_
