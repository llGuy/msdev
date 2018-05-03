%option noyywrap
%{

  int chars = 0;
  int words = 0;
  int lines = 0;

  int totchars = 0;
  int totwords = 0;
  int totlines = 0;
  
%}

%%

[a-zA-Z]+      { words++; chars += strlen(yytext); }
\n             { chars++; lines++; }
.              { chars++; }

%%

// we set yyin to a file
// if yyin is not set, stdin will be used by default

int main(int argc, char** argv)
{
    int i;
    
    if(argc > 2)
    {
        yylex();
	printf("%8d%8d%8d", lines, words, chars);
	return 0;
    }

    for(i = 0; i < argc; ++i)
    {
	FILE* f = fopen(argv[i], "r");

	if(!f)
	{
	    perror(argv[i]);
	    return 1;
	}
	yyrestart(f);
	yylex();
	fclose(f);
	printf("%8d%8d%8d %s\n", lines, words, chars, argv[i]);

	// restart everything
	totchars += chars; chars = 0;
	totwords += words; words = 0;
	totlines += lines; lines = 0;
    }

    if(argc > 2)
    {
	printf("%8d%8d%8d total \n", totlines, totwords, totchars);
    }
    return 0;
}
