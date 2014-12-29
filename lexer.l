%option noyywrap

%{
	#include "parser.tab.h"
	int yylex();
%}

%x IN_COMMENT

num [0-9]+
identifier [_a-z]+

%%

<IN_COMMENT>"*)"	BEGIN(INITIAL);
<IN_COMMENT>.*	;


"(*"		BEGIN(IN_COMMENT);
[ \t\r\n]+	;

/* Commands */
"ASSIGN"	return ASSIGN;
"IF"		return IF;
"THEN"		return THEN;
"ENDIF"		return ENDIF;
"ELSE"		return ELSE;
"WHILE"		return WHILE;
"DO"		return DO;
"ENDWHILE"	return ENDWHILE;
"GET"		return GET;
"PUT"		return PUT;

/* Expressions */
"PLUS"		return PLUS;
"MINUS"		return MINUS;
"TIMES"		return MUL;
"DIV"		return DIV;
"MOD"		return MOD;

/* Conditions */
"EQ"		return EQ;
"DIFF"		return DIFF;
"LE"		return LE;
"GE"		return GE;
"LEQ"		return LEQ;
"GEQ"		return GEQ;

/* Values */
num			return NUM;
identifier	return IDENTIFIER;




%%