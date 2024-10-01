#ifndef _BASE_MESSAGE_H_
#define _BASE_MESSAGE_H_

#include <iostream>
#include <unordered_map>

class BaseMessage
{
public:
	BaseMessage() = default;
	~BaseMessage() = default;

	BaseMessage(const std::string name) :
		name(name), 
		msg_table(std::unordered_map<std::string, std::string>()) { }

	BaseMessage(const std::string name, std::unordered_map<std::string, std::string> msg_table) :
		name(name),msg_table(msg_table) { }

	void set_property(const std::string tag, std::string msg);

	const std::string get_property(const std::string tag);

	void set_name(const std::string name);

	const std::string get_name();

	friend std::ostream& operator<<(std::ostream& os, const BaseMessage& msg);

private:
	std::string name;
	std::unordered_map<std::string, std::string> msg_table;

};

#endif // !_BASE_MESSAGE_H_
