YACC=/usr/local/Cellar/bison/3.0.2/bin/bison
YACC_SRC=src/parser.y

LEX=/usr/local/Cellar/flex/2.5.37/bin/flex
LEX_SRC=src/lexer.l

CC=/usr/local/Cellar/gcc/4.9.2_1/bin/gcc-4.9
CC_OUTPUT=fuzzybear-cc

all: 
	 $(YACC) -d $(YACC_SRC)
	 $(LEX) $(LEX_SRC)
	 $(CC) -o $(CC_OUTPUT) lex.yy.c parser.tab.c -lm -std=c11

clean:
	rm -f parser.tab.c parser.tab.h lex.yy.cc $(CC_OUTPUT) interpreter

interpreter:
	g++ -o interpreter src/interpreter.cc