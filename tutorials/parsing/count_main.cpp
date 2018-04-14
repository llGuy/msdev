#include <stdio.h>

extern int yylex();
extern int nlines;
extern int nchars;

int main(int argc, char**argv){
	yylex();
	printf( "%8s%8s\n", "lines", "chars" );
	printf( "%8d%8d\n", nlines, nchars );
}
