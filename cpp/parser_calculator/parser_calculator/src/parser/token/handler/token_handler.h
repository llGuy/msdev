#ifndef TOKEN_HANDLER_HEADER
#define TOKEN_HANDLER_HEADER

#include <vector>
#include "../../expr/expr.h"
#include "../token/token.h"
#include "../../utility.h"

namespace parser
{
	class TkHandler
	{
	public:
		explicit TkHandler(void);
	public:
		// tokenize an expression
		const std::vector<Token> Tk(const Expr& expr) const;
	private:
		//typedef const bool(*isfunc_t)(const char);
		const Token GenNumTk(const Expr& e, uint32_t& i, bool&) const;
		const Token GenBrackTk(const Expr& e, uint32_t& i, bool&) const;
		const Token GenOperTk(const Expr& e, uint32_t& i, bool&) const;
		const Token GenSingleCTk(const Expr& e, uint32_t& i, bool&, const token_t) const;
	private:
		const bool IsNum(const char) const;
		const bool IsBracket(const char) const;
		const bool IsOperator(const char) const;
	};
}

#endif