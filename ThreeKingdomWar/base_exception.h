#ifndef _BASE_EXCEPTION_H_
#define _BASE_EXCEPTION_H_

#include <stdexcept>
#include <iostream>
#include <string>

#include "base_message.h"

class BaseException
{
public:
	void set_error_message(BaseMessage* msg);

	const BaseMessage* get_error_message();

private:
	BaseMessage* msg;
};


#endif // !_BASE_EXCEPTION_H_
