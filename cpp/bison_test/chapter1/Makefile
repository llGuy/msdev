parser: lex.yy.o
	cc -o parser lex.yy.o -lfl

lex.yy.o: lex.yy.c
	cc -c lex.yy.c

lex.yy.c: conj.y
	flex conj.y

# part of the makefile
fb1-5: fb1-4.l fb1-5.y
	bison -d fb1-5.y
	flex fb1-4.l
	cc -o $@ fb1-5.tab.c lex.yy.c -lfl
