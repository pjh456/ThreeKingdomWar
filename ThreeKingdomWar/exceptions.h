#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <iostream>
#include <string>

#include "base_exception.h"

class UnknownTokenError :public BaseException
{
public:
	UnknownTokenError();
	UnknownTokenError(int pointer);

};

class UnknownExpressionError :public BaseException
{
public:
	UnknownExpressionError();
	UnknownExpressionError(int pointer);

};

class ListError :public BaseException
{
public:
	ListError();
	ListError(int pointer);

};

class StatementError :public BaseException
{
public:
	StatementError();
	StatementError(int pointer);

};

#endif // !_EXCEPTIONS_H_
