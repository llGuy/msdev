#ifndef TOKEN_HEADER
#define TOKEN_HEADER

#include <string>

namespace parser
{
	enum class token_t
		: uint8_t
	{
		NUMBER,

		OPERATOR,

		BRACKET
	};

	struct Token
	{
		std::string tk;
		token_t type;
	};
}

#endif