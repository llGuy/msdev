%option noyywrap

%{
#include "obj2ogl_grammar.hpp"

%}

%x COMMENT

%%

[0-9]+	{ return tNUMBER; }
[0-9]+\.[0-9]+	 { return tNUMBER; }

"v"	{ return tVERTEX; }
"vp" { return tVERTEX_PARAM; }
"f" { return tVERTEX_INDEX; }

"#" { BEGIN(COMMENT); }
<COMMENT>{
.	{}
\n	{ BEGIN(INITIAL); }

}

%%