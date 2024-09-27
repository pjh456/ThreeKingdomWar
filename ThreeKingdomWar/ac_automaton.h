#ifndef _AC_AUTOMATON_H_
#define _AC_AUTOMATON_H_

#include <string>
#include <vector>

#include "token.h"

/*
// 用于匹配词法分析器
class ACAutoMaton
{
public:
	ACAutoMaton() = default;
	~ACAutoMaton() = default;

	// 查询保留字
	const TokenType find_key(const std::string input)
	{
		Node* current_node = this->get_node(input);
		return current_node ? current_node->get_type() : TokenType::ERROR;
	}

	// 添加一个新的保留字
	void add_key(const std::string key, const TokenType type)
	{
		Node* current_node = this->get_node(key, true);	// 新建一个无映射节点
		current_node->set_type(type);	// 给节点添加语义类型映射
	}

private:
	// 自动机节点
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

		// 添加一个新节点，但路径上的节点是不可用的，所以用 ERROR 替代
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
		char ch;							// 节点上的字符
		int count = 0;						// 记录路径上节点个数
		TokenType type = TokenType::ERROR;	// 对应的语义标记
		Node* nodes[200] = { nullptr };		// 子节点

	};

	// 直接查找节点指针，可选是否创建新节点
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
