CC   = ""
YACC = ""
LEX  = ""

all: 
	/usr/local/Cellar/bison/3.0.2/bin/bison -d parser.y
	/usr/local/Cellar/flex/2.5.37/bin/flex lexer.l
	/usr/local/Cellar/gcc/4.9.2_1/bin/gcc-4.9 -o fbcc lex.yy.c parser.tab.c -lm -std=c11

clean:
	rm -f parser.tab.c parser.tab.h lex.yy.c fbcc current.results
