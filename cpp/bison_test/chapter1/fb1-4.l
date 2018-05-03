%{

  #include "fb1-5.tab.h"
  
%};

%%

"+"     { return ADD; }
"-"     { return SUB; }
"*"     { return MUL; }
"/"     { return DIV; }
"|"     { return ABS; }
"("     { return OP; }
")"     { return CP; }
"//".*  { /* ignore comments */ }
[0-9]+  { yylval = atoi(yytext); return NUMBER; }
\n      { return EOL; }
[ \t]    { /* ignore white space */ }
.       { printf("Mystery character %c\n", *yytext); }

%%

