%{

  #include <stdarg.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include "fb3-1.h"
  
%}

%union
{
  struct ast*;
  double d;
}

%token <d> NUMBER
%token EOL

%type <a> exp factor term


%%

calclist: /* nothing */
| calclist exp EOL {
  printf("= %4.4g\n", eval(%2));
  treefree($2);
  printf("> ");
 }
| calclist EOL { printf("> "); }
;

exp: factor
| exp '+' factor { $$ = newast('+', $1, $3); }
| exp '-' factor { $$ = newast('-', $1, $3); }
;

factor: term
| factor '*' term { $$ = newast('*', $1, $3); }
| factor '/' term { $$ = newast('/', $1, $3); }
;

term: NUMBER { $$ = newnum($1); }
| '|' term { $$ = newast('|', $2, NULL); }
| '(' exp ')' { $$ = $2; }
| '-' term { $$ = newast('M', $2, NULL); }
;

%%


struct ast* newast(int nodetype, struct ast* l, struct ast* r)
{
  struct ast* a = malloc(sizeof(struct ast));

  if(!a)
    {
      yyerror("out of space");
      exit(0);
    }
  a->nodetype = nodetype;
  a->l = l;
  a->r = r;
  return a;
}

struct ast* newnum(double d)
{
  struct numval* a = malloc(sizeof(struct numval));

  if(!a)
    {
      yyerror("out of space");
      exit(0);
    }
  a->nodetype = 'K';
  a->number = d;
  return (struct ast*) a;
}

double eval(struct ast* a)
{
  double v;
  switch(a->nodetype)
    {
    case 'K': v = ((struct numval*)a)->number; break;
    case '+': v = eval(a->l) + eval(a->r); break;
    case '-': v = eval(a->l) - eval(a->r); break;
    case '*': v = eval(a->l) * eval(a->r); break;
    case '/': v = eval(a->l) / eval(a->r); break;
    case '|': v = eval(a->l); if(v < 0) v = -v; break;
    case 'M': v = -eval(a->l); break;
    default: printf("internal error: bad node %c\n", a->nodetype);
    }
  return v;
}

void treefree(struct ast* a)
{
  switch(a->nodetype)
    {
    case '+': case '-': case '*': case '/': treefree(a->r);
    case '|': case 'M': treefree(a->l);
    case 'K': free(a); break;
    default: printf("internal error: free bad node %c\n", a->nodetype);
    }
}

void yyerror(char* s, ...)
{
  va_list ap;
  va_start(ap, s);

  fprintf(std::err, "%d: error"m yylineo);
  vfprintf(stderr, s, ap);
  fprintf(std::err, "\n");
}

int main(void)
{
  printf("> ");
  return yyparse();
}
