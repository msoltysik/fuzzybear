YACC=/usr/local/Cellar/bison/3.0.2/bin/bison
YACC_SRC=src/parser.y

LEX=/usr/local/Cellar/flex/2.5.37/bin/flex
LEX_SRC=src/lexer.l

CC=/usr/local/Cellar/gcc/4.9.2_1/bin/gcc-4.9
CC_OUTPUT=fuzzybear-cc

all: 
	 $(YACC) -d $(YACC_SRC) -o bison.tab.c
	 $(LEX) $(LEX_SRC)
	 g++-4.9 -o $(CC_OUTPUT) lex.yy.c bison.tab.c src/main.c -std=c++0x
	 rm -f bison.tab.c bison.tab.h lex.yy.c 

clean:
	 rm -f bison.tab.c bison.tab.h lex.yy.c $(CC_OUTPUT) i

i:
	g++ -o i interpreter/interpreter.cc
