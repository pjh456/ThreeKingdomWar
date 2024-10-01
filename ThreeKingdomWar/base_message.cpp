#include "base_message.h"

void BaseMessage::set_property(const std::string tag, std::string msg)
{
	this->msg_table[tag] = msg;
}

const std::string BaseMessage::get_property(const std::string tag)
{
	return msg_table[tag];
}

void BaseMessage::set_name(const std::string name)
{
	this->name = name;
}

const std::string BaseMessage::get_name()
{
	return name;
}


std::ostream& operator<<(std::ostream& os, const BaseMessage& msg)
{
	os << "Message " << msg.name << " :[\n";
	for (const auto& pair : msg.msg_table)
	{
		os << pair.first << " : " << pair.second << "\n";
	}
	os << "]\n";
	return os;
}