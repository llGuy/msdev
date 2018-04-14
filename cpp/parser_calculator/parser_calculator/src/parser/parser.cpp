#include "parser.h"

namespace parser
{
	Parser::Parser(const Expr& expr)
		: m_expr(expr), m_tkhandler()
	{
	}
	void Parser::Parse(void)
	{
		// test to check if tokenizer works
		std::vector<Token> tks = m_tkhandler.Tk(m_expr);
		for (auto& t : tks)
		{
			std::cout << t.tk << " " << static_cast<uint32_t>(t.type) << std::endl;
		}
	}
}