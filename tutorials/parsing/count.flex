%option noyywrap

%{
int nlines = 0;
int nchars = 0;
%}

%%

\n	{ nlines++; };
.	{ nchars++; };

%%


