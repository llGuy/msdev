#include "token_handler.h"

namespace parser
{
	TkHandler::TkHandler(void)
	{
	}
	const std::vector<Token> TkHandler::Tk(const Expr& expr) const
	{
		std::vector<Token> tks;
		uint32_t index = 0;
		while(expr.expression[index] != '\0')
		{
			char c = expr.expression[index];
			bool valid = false;

			if (IsNum(c)) tks.push_back(GenNumTk(expr, index, valid));
			if (IsBracket(c)) tks.push_back(GenBrackTk(expr, index, valid));
			if (IsOperator(c)) tks.push_back(GenOperTk(expr, index, valid));
			if (!valid) ++index;
		}

		return tks;
	}
	const Token TkHandler::GenNumTk(const Expr& e, uint32_t& i, bool& valid) const
	{
		valid = true;
		Token t;
		t.type = token_t::NUMBER;
		do
		{
			t.tk.push_back(e.expression[i]);
			++i;
		} while(IsNum(e.expression[i]));

		return t;
	}
	const bool TkHandler::IsNum(const char c) const
	{
		return c >= ASCII0 && c <= ASCII9;
	}
	const bool TkHandler::IsBracket(const char c) const
	{
		return c == CBRACKET || c == OBRACKET;
	}
	const bool TkHandler::IsOperator(const char c) const
	{
		return c == OPERATOR[PLUS] ||
			c == OPERATOR[MINUS] ||
			c == OPERATOR[TIMES] ||
			c == OPERATOR[DIVIDE];
	}
	const Token TkHandler::GenBrackTk(const Expr& e, uint32_t& i, bool& valid) const
	{
		return GenSingleCTk(e, i, valid, token_t::BRACKET);
	}
	const Token TkHandler::GenOperTk(const Expr& e, uint32_t& i, bool& valid) const
	{
		return GenSingleCTk(e, i, valid, token_t::OPERATOR);
	}
	const Token TkHandler::GenSingleCTk(const Expr& e, uint32_t& i, bool& valid, const token_t t) const
	{
		valid = true;
		Token tk;
		tk.type = t;
		tk.tk = e.expression[i];
		++i;
		return tk;
	}
}