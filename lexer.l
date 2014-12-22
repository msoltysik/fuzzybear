%option noyywrap

%{
	#include "parser.tab.h"
	int yylex();
%}

%x SLASH IN_COMMENT IN_M_COMMENT
identifier [_a-z]+

%%

"PLUS"		return PLUS;
"MINUS"		return MINUS;
"TIMES"		return MUL;
"DIV"		return DIV;
"MOD"		return MOD;

"EQ"		return EQ;
"DIFF"		return DIFF;
"LE"		return LE;
"GE"		return GE;
"LEQ"		return LEQ;
"GEQ"		return GEQ;

"ASSIGN"	return ASSIGN;

"GET"		return GET;
"PUT"		return PUT;


%%