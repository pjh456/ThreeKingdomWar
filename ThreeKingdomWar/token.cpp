
#include "token.h"


std::ostream& operator<<(std::ostream& os, const Token& token)
{
	return os << "Token<" << static_cast<int>(token.type) << ", " << token.value << ">";
}
