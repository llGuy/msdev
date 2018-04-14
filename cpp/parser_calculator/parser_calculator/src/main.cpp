#include "parser/parser.h"

int main(int argc, char* argv[])
{
	parser::Parser p({ "12*2+1 * (2 -1124)" });
	p.Parse();

	std::cin.get();
}