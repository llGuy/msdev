%option noyywrap
%option yylineno

%{
#include <iostream>
using namespace std;
#include "obj2ogl_grammar.hpp"
#pragma clang diagnostic ignored "-Wdeprecated-register"
%}

%x COMMENT

%%

[0-9]+	{ return tINTEGER; }
[0-9]+\.[0-9]+	 { return tNUMBER; }
"-"[0-9]+\.[0-9]+	 { return tNUMBER; }

^"v" { return tVERTEX; }
^"vp" { return tVERTEX_PARAM; }
^"f" {  return tVERTEX_INDEX; }
^"o" { return tOBJECT_NAME; }
^"mtllib" { return tMATERIAL_NAME; }
^"usemtl" { return tUSE_MATERIAL; }
^"vn" { return tVERTEX_NORMAL; }
^"vt" { return tTEXTURE_COORD; }
^"s" { return tSMOOTH; }
^"g" { return tGROUP_NAME; }

[_\.a-zA-Z]+	  { return tSTRING_VALUE; }

"//"		  { return tDOUBLE_SLASH; }
"/"			  { return tSLASH; }

"#" { BEGIN(COMMENT); }
<COMMENT>{
.	{}
\n	{ BEGIN(INITIAL); }
}


[ \t\n]           {}

%%