#ifndef _AC_AUTOMATON_H_
#define _AC_AUTOMATON_H_

#include <string>
#include <vector>

#include "token.h"


// 用于匹配词法分析器
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

	// 查询保留字
	const TokenType find_key(const std::string input)
	{
		Node* current_node = this->get_node(input);
		return current_node ? current_node->get_type() : TokenType::UNKNOWN;
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

		// 添加一个新节点，但路径上的节点是不可用的，所以用 UNKNOWN 替代
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
		ACAutoMaton* parent;				// 所属AC自动机
		char ch;							// 节点上的字符
		int count = 0;						// 记录路径上节点个数
		TokenType type = TokenType::UNKNOWN;	// 对应的语义标记
		Node* nodes[256] = { nullptr };		// 子节点

	};

	// 直接查找节点指针，可选是否创建新节点
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
