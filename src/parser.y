%{
    #include <iostream>
    #include <string>
    #include <vector>
	
	int yylex();

    using namespace std;
%}

%union {
	string num;
	string identifier;
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
				}
				;

vdeclarations:	vdeclarations identifier
				{
				}
				|
				{
				}
				;

commands:		commands command
				|
				;

command:		identifier ASSIGN expression SEM
				{
				}
				| IF condition THEN commands ENDIF
				{
				}
				| IF condition THEN commands ELSE commands ENDIF
				{
				}
				| WHILE condition DO commands ENDWHILE
				{
				}
				| GET identifier SEM
				{
				}
				| PUT value SEM
				{
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
				}
				| identifier
				{
				}
				;
%%

