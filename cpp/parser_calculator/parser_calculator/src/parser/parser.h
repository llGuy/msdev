#ifndef PARSER_HEADER
#define PARSER_HEADER

#include <iostream>
#include "expr/expr.h"
#include "token/handler/token_handler.h"

namespace parser
{
	class Parser
	{
	public:
		explicit Parser(const Expr& expr);
	public:
		void Parse(void);
	private:
		const Expr m_expr;
		const TkHandler m_tkhandler;
	};
}

#endif