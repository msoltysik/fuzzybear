%{
	#include <stdio.h>
	void yyerror(char *errorinfo);
	int yylex(void);
	int yylineno;
	extern FILE *yyin;
	extern FILE *yyout;
	int dbg = 1;

	void DBG(int linenumber, char* keyword);
	void DBGwithValue(int linenumber, char* keyword, char* value);
%}

%union {
	char *num;
	char *identifier;
}

%token <identifier> DECLARE;
%token <identifier> IN;
%token <identifier> END;

%token <identifier> ASSIGN;
%token <identifier> IF;
%token <identifier> THEN;
%token <identifier> ENDIF;
%token <identifier> ELSE;
%token <identifier> WHILE;
%token <identifier> DO;
%token <identifier> ENDWHILE;
%token <identifier> GET;
%token <identifier> PUT;

%token <identifier> PLUS;
%token <identifier> MINUS;
%token <identifier> TIMES;
%token <identifier> DIV;
%token <identifier> MOD;

%token <identifier> EQ;
%token <identifier> DIFF;
%token <identifier> LE;
%token <identifier> GE;
%token <identifier> LEQ;
%token <identifier> GEQ;

%token <num> num;
%token <identifier> identifier;

%token <identifier> SEM;

%%
program:		DECLARE vdeclarations IN commands END
				{
					DBG(yylineno, "END");
				}
				;

vdeclarations:	vdeclarations identifier
				{
					DBGwithValue(yylineno, "IDENTIFIER", $2);
				}
				|
				{
					DBG(yylineno, "DECLARE");
				}
				;

commands:		commands command {}
				| {}
				;

command:		identifier ASSIGN expression SEM
				{
					DBGwithValue(yylineno, "ASSIGN", yylval.identifier);
				}
				| IF condition THEN commands ENDIF
				{
					DBG(yylineno, "IF/THEN/ENDIF");
				}
				| IF condition THEN commands ELSE commands ENDIF
				{
					DBG(yylineno, "IF/THEN/ELSE/ENDIF");
				}
				| WHILE condition DO commands ENDWHILE
				{
					DBG(yylineno, "WHILE/DO/ENDWHILE");
				}
				| GET identifier SEM
				{
					DBGwithValue(yylineno, "GET", $2);
				}
				| PUT value SEM
				{
					DBG(yylineno, "PUT");
				}
				;
expression:		value {}
				| value PLUS value
				{
					DBG(yylineno, "PLUS");
				}
				| value MINUS value
				{
					DBG(yylineno, "MINUS");
				}
				| value TIMES value
				{
					DBG(yylineno, "TIMES");
				}
				| value DIV value
				{
					DBG(yylineno, "DIV");
				}
				| value MOD value
				{
					DBG(yylineno, "MOD");
				}
				;
condition:		value EQ value
				{
					DBG(yylineno, "EQ");
				}
				| value DIFF value
				{
					DBG(yylineno, "DIFF");
				}
				| value LE value
				{
					DBG(yylineno, "LE");
				}
				| value GE value
				{
					DBG(yylineno, "GE");
				}
				| value LEQ value
				{
					DBG(yylineno, "LEQ");
				}
				| value GEQ value
				{
					DBG(yylineno, "GEQ");
				}
				;
value:			num
				{
					DBGwithValue(yylineno, "NUM", yylval.num);
				}
				| identifier
				{
					DBGwithValue(yylineno, "IDENTIFIER", yylval.identifier);
				}
				;
%%

void yyerror(char *s)
{
      printf("Błąd w linii %d: %s \n", yylineno, s);
}

void DBG(int linenumber, char* keyword) {
	if (dbg == 1) {
		printf("[%d]: <%s>\n", linenumber, keyword);
	}
}

void DBGwithValue(int linenumber, char* keyword, char* value) {
	if (dbg == 1) {
		printf("[%d]: <%s>: %s\n", linenumber, keyword, value);
	}
}

///*
int main(int argc, char **argv) {
    ++argv, --argc;  /* skip over program name */
	printf("Fuzzy Bear CC.\nCopyright (c) 2015.\nMateusz Sołtysik, JFTT @ WPPT.\n\n");

	switch(argc) {
		case 1:
				yyin 	= fopen(argv[0], "r");
				yyparse();
				break;
		case 2:
				yyin 	= fopen(argv[0], "r");
				yyout 	= freopen(argv[1], "w", stdout);
				yyparse();
				fclose(yyout);
				break;	
		default:
				printf("Usage:\n$ ./fuzzybear-cc in.imp (or)\n$ ./fuzzybear-cc in.imp out.mr\n");

	}
	return 0;
}
//*/