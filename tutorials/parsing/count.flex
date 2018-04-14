%option noyywrap

%{
int nlines = 0;
int nchars = 0;
int nluc =0;
#pragma clang diagnostic ignored "-Wdeprecated-register"
%}

%%

\n	{ nlines++; };
.	{ nchars++; };
luc	{ nluc++; };

%%


