%{
	#include <stdio.h>
	void yyerror(char *errorinfo);
	int yylex(void);
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

%token num;
%token identifier;

%token SEM;

%%
program:
DECLARE vdeclarations IN commands END {printf("Dupa0.0\n");}
;

vdeclarations:
vdeclarations identifier  {printf("Dupa1.1\n");}
| {printf("Dupa1.2\n");}
;

commands:
commands command
|
;

command:
identifier ASSIGN expression;
| IF condition THEN commands ENDIF
| IF condition THEN commands ELSE commands ENDIF
| WHILE condition DO commands ENDWHILE
| GET identifier SEM
| PUT value SEM
;

expression:
value
| value PLUS value
| value MINUS value
| value TIMES value
| value DIV value
| value MOD value
;

condition:
value EQ value
| value DIFF value
| value LE value
| value GE value
| value LEQ value
| value GEQ value
;

value:
num
| identifier
;
%%

void yyerror(char *errorinfo) {
	printf("%s\n", errorinfo);
}

int main(int argc, char **argv) {
	yyparse();
	return 0;
}