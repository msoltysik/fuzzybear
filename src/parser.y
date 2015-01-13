%{
	// BEGIN INCLUDES
	#include <stdio.h>
	#include <stdbool.h>
	#include <stdlib.h>
	#include <string.h>
	// END INCLUDES


	// BEGIN STRUCTURES
	typedef struct {
		char* name;
		char* value;
	} st_identifier;

	typedef struct {
		st_identifier stack[100];
		int top;
	} st_identifier_stack;
	// END STRUCTURES

	// BEGIN CONSTANT
	bool DEBUGER_MODE = false;
	st_identifier_stack *identifier_stack;
	// END CONSTANT

	// BEGIN FUNCTION PROTOTYPES
	void yyerror(char *errorinfo);
	int yylex(void);
	int yylineno;
	extern FILE *yyin;
	extern FILE *yyout;
	void DBG(int linenumber, char* keyword);
	void DBGwithValue(int linenumber, char* keyword, char* value);
	// END FUNCTION PROTOTYPES

	// SYF
	st_identifier * identifier_new(char* name) {
		st_identifier *i = malloc(sizeof(st_identifier));
		i->name = name;
		i->value = NULL;
		return i;
	}

	void identifier_free(st_identifier *i) {
		if (i->name)
			free(i->name);
		if (i->value)
			free(i->value);
		free(i);
	}

	void identifier_stack_new() {
		identifier_stack = malloc(sizeof(identifier_stack));
		identifier_stack->top = 0;
	}

	void identifier_stack_push(st_identifier i) {
		identifier_stack->stack[identifier_stack->top++] = i;
	}

	st_identifier identifier_stack_pop() {
		return identifier_stack->stack[identifier_stack->top--];
	}

	bool identifier_on_stack(char *identifier_name) {
		for (int i = 0; i < identifier_stack->top; i++) {
    		if (!strcmp(identifier_stack->stack[i].name, identifier_name)) {
				return true;    			
    		}
		}
		return false;
	}

	char* concat(char *s1, char *s2) {
	    char *result = malloc(strlen(s1) + strlen(s2) + 1);
	    strcpy(result, s1);
	    strcat(result, s2);
	    return result;
	}



	// END SYF
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
					
					if (identifier_on_stack($2)) {
						yyerror(concat("druga deklaracja ", $2));
					} else {
						st_identifier *i = identifier_new($2);
						identifier_stack_push(*i);
					}
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

					if (!identifier_on_stack($2)) {
						yyerror(concat("niezadeklarowana zmienna ", $2));
					}

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

	identifier_stack = malloc(sizeof(identifier_stack));
	identifier_stack->top = 0;

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