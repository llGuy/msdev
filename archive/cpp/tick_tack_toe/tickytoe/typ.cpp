#include "typ.h"

typ::typ()
{
}
void typ::eff(string text)
{
	int x=0;
	while(text[x]!='\0')
	{
	cout<<text[x];
	Sleep(rand()%25+25);
	x++;
	}
}
typ::~typ()
{
}
