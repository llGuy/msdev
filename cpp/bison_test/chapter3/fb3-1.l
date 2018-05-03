%{

#include "fb3-1.h"
#include "fb3-1.tab.h"

%}

/* float exponent */
EXP ([Ee][-+]?[0-9]+)

%%

"+" |
"-" |
"*" |
"/" |
"|" |
"(" |
")"    { return yytext[0]; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yyval.d = atof(yytext); return NUMBER; }

\n { return EOL; }
"//".* 
[ \t]{  /* ignore whitespace */ }
. { yyerror("Mystery character %c\n", *yytext); }

%%
