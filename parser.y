%{
	#include <stdio.h>
	void yyerror(char *errorinfo);
	int yylex(void);
	int yylineno;

	void DBG(int linenumber, char* keyword) {
		printf("[%d]: <%s>\n", linenumber, keyword);
	}

	void DBGwithValue(int linenumber, char* keyword, char* value) {
		printf("[%d]: <%s>: %s\n", linenumber, keyword, value);
	}

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
program:		{}
				| DECLARE vdeclarations IN commands END
				{
					DBG(yylineno, "End of Program");
				}
				;

vdeclarations:	vdeclarations identifier
				{
					DBGwithValue(yylineno, "ID", yylval.identifier);
				}
				|
				{
					DBG(yylineno, "vdeclarations");
				}
				;

commands:		commands command
				{
					DBG(yylineno, "commands");
				}
				|
				{}
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
					DBGwithValue(yylineno, "GET", yylval.identifier);
				}
				| PUT value SEM
				{
					DBG(yylineno, "PUT");
				}
				;
expression:		value {}
				| value PLUS value
				{

				}
				| value MINUS value
				{

				}
				| value TIMES value
				{

				}
				| value DIV value
				{

				}
				| value MOD value
				{

				}
				;
condition:		value EQ value
				{

				}
				| value DIFF value
				{

				}
				| value LE value
				{

				}
				| value GE value
				{

				}
				| value LEQ value
				{

				}
				| value GEQ value
				{

				}
				;
value:			num
				{
					DBGwithValue(yylineno, "NUM", yylval.num);
				}
				| identifier
				{
					DBGwithValue(yylineno, "ID", yylval.identifier);
				}
				;
%%

void yyerror(char *errorinfo) {
	printf("%s\n", errorinfo);
}

///*
int main(int argc, char **argv) {
	yyparse();
	return 0;
}
//*/