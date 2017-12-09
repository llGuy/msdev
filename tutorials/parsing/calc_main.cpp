#include <iostream>
#include "calc_ast.h"

AST * root;

extern void yyparse();
extern void parse_string( const char * str );

using namespace std;
void yyerror(char*s){
	cout << "ERROR: " << s << endl;
}

int main(int argc, char * argv[] ){
	//parse_string( "2*3+2");
	yyparse();

	cout << "CPP: " << root->value() << endl;
}
