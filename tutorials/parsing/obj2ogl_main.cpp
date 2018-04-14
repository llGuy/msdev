#include <iostream>
using namespace std;


extern void yyparse();
extern int yylex();
extern int yylineno;
void yyerror(char*s){
	cout << "ERROR: (" << yylineno << ") " << s << endl;
}

int main(int argc, char*argv[]){
	

	yyparse();
	//while(yylex());
	
	return 0;
}
