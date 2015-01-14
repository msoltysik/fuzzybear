%{
	// BEGIN INCLUDES
	#include <stdio.h>
	#include <stdbool.h>
	#include <stdlib.h>
	#include <string.h>
	#include "src/compiler.h"

	bool DEBUGER_MODE = true;

	void yyerror(char *errorinfo);
	int yylex(void);
	int yylineno;
	extern FILE *yyin;
	extern FILE *yyout;
	void DBG(int linenumber, char* keyword);
	void DBGwithValue(int linenumber, char* keyword, char* value);
%}

%union {
	char *num;
	char *identifier;
}

%token DECLARE;
%token IN;
%token END;

%token ASSIGN;
%token IF;
%token THEN;
%token ENDIF;
%token ELSE;
%token WHILE;
%token DO;
%token ENDWHILE;
%token GET;
%token PUT;

%token PLUS;
%token MINUS;
%token TIMES;
%token DIV;
%token MOD;

%token EQ;
%token DIFF;
%token LE;
%token GE;
%token LEQ;
%token GEQ;

%token <num> num;
%token <identifier> identifier;
%token <identifier> SEM;

%type <num> value


%%
program:		DECLARE vdeclarations IN commands END
				{
					DBG(yylineno, "END");
					end_of_program();
				}
				;

vdeclarations:	vdeclarations identifier
				{
					DBGwithValue(yylineno, "IDENTIFIER", $2);
					define_variable($2);
				}
				|
				{
					DBG(yylineno, "DECLARE");
				}
				;

commands:		commands command
				|
				;

command:		identifier ASSIGN expression SEM
				{
					DBGwithValue(yylineno, "ASSIGN", yylval.identifier);
					assign_variable($1);
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
					get_variable($2);
				}
				| PUT value SEM
				{
					DBG(yylineno, "PUT");
					put_variable($2);
				}
				;
expression:		value {}
				| value PLUS value
				{
					DBG(yylineno, "PLUS");
					plus_expression($1, $3);
				}
				| value MINUS value
				{
					DBG(yylineno, "MINUS");
					minus_expression($1, $3);
				}
				| value TIMES value
				{
					DBG(yylineno, "TIMES");
					times_expression($1, $3);
				}
				| value DIV value
				{
					DBG(yylineno, "DIV");
					div_expression($1, $3);
				}
				| value MOD value
				{
					DBG(yylineno, "MOD");
					mod_expression($1, $3);
				}
				;
condition:		value EQ value
				{
					DBG(yylineno, "EQ");
					eq_condition($1, $3);
				}
				| value DIFF value
				{
					DBG(yylineno, "DIFF");
					diff_condition($1, $3);
				}
				| value LE value
				{
					DBG(yylineno, "LE");
					le_condition($1, $3);
				}
				| value GE value
				{
					DBG(yylineno, "GE");
					ge_condition($1, $3);
				}
				| value LEQ value
				{
					DBG(yylineno, "LEQ");
					leq_condition($1, $3);
				}
				| value GEQ value
				{
					DBG(yylineno, "GEQ");
					geq_condition($1, $3);
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
      exit(-4);
}



void DBG(int linenumber, char* keyword) {
	if (DEBUGER_MODE) {
		printf("[%d]: <%s>\n", linenumber, keyword);
	}
}

void DBGwithValue(int linenumber, char* keyword, char* value) {
	if (DEBUGER_MODE) {
		printf("[%d]: <%s>: %s\n", linenumber, keyword, value);
	}
}

///*
int main(int argc, char **argv) {
    ++argv, --argc;  /* skip over program name */
	printf("Fuzzy Bear CC.\nCopyright (c) 2015.\nMateusz Sołtysik, JFTT @ WPPT.\n\n");

	switch(argc) {
		case 1:
				yyin = fopen(argv[0], "r");

				init_cc();
				yyparse();
				generate_cc();
				free_cc();
				break;
		case 2:
				yyin  = fopen(argv[0], "r");
				yyout = freopen(argv[1], "w", stdout);

				init_cc();
				yyparse();
				fclose(yyout);
				free_cc();
				break;	
		default:
				printf("Usage:\n$ ./fuzzybear-cc in.imp (or)\n$ ./fuzzybear-cc in.imp out.mr\n");

	}
	return 0;
}
//*/