/* simplest version of a calculator */
%{

#include <stdio.h>

%}

/* declare tokens */
%token OP CP 
%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL

%%

   /*
     
     exp: exp ADD exp
     | exp SUB exp
     | exp MUL exp
     | exp DIV exp
     | ABS exp
     | NUMBER
     ;
     
     why not do this? precedence and ambiguity. The separate symbols term, factor 
     and exp tell bison to handle ABD, then MUL and DIV, and then ADD and SUB. 
     In general, whenever a grammar has multiple levels of precedence where one kind
     of operator binds "tighter" than another, the parser will need a level of rule
     for each level.

    */
   
calclist: /* nothing */
| calclist exp EOL { printf(" = %ld\n", $2); }
;

exp: factor
     | exp ADD factor { $$ = $1 + $3; }
| exp SUB factor { $$ = $1 - $3; }
;

factor: term
| factor MUL term { $$ = $1 * $3; }
| factor DIV term { $$ = $1 / $3; }
;

 term: NUMBER 
| ABS term { $$ = $2 >= 0 ? $2 : -$2; }
| OP exp CP { $$ = $2; }
;

%%

int main(int argc, char** argv)
{
  yyparse();
}

int yyerror(char* s)
{
  fprintf(stderr, "error: %s\n", s);
}
