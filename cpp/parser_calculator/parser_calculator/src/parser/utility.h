#ifndef UTILITY_HEADER
#define UTILITY_HEADER

#include <stdint.h>

constexpr uint32_t ASCII0 = 48;
constexpr uint32_t ASCII9 = 57;

constexpr char OBRACKET = '(';
constexpr char CBRACKET = ')';

enum operator_t
{
	PLUS,

	MINUS,

	TIMES,

	DIVIDE
};

constexpr char OPERATOR[4]
{
	'+', '-', '*', '/'
};

#endif