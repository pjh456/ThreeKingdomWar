#include "base_exception.h"


void BaseException::set_error_message(BaseMessage* msg)
{
	this->msg = msg;
}

const BaseMessage* BaseException::get_error_message()
{
	return msg;
}