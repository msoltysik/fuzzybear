%option noyywrap
%option yylineno

%{
	#include <stdlib.h>
	#include "parser.tab.h"
	int yylex();
%}

%x IN_COMMENT

%%

<IN_COMMENT>"*)"	BEGIN(INITIAL);
<IN_COMMENT>.		;
<IN_COMMENT>"\n"		;

"(*"		BEGIN(IN_COMMENT);
[ \t\r\n]+	;

"DECLARE"	return DECLARE;
"IN"		return IN;
"END"		return END;

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

"PLUS"		return PLUS;
"MINUS"		return MINUS;
"TIMES"		return TIMES;
"DIV"		return DIV;
"MOD"		return MOD;

"EQ"		return EQ;
"DIFF"		return DIFF;
"LE"		return LE;
"GE"		return GE;
"LEQ"		return LEQ;
"GEQ"		return GEQ;

[_a-z]+		{
				yylval.identifier = (char *)strdup(yytext);
             	return(identifier); 
            }
[0-9]+		{
				yylval.num = (char *)strdup(yytext);
             	return(num);
            }
";"			return SEM;
.			;

%%


/*
YYSTYPE yylval;
int main(void)
{
    int token;
    while ((token = yylex()) != 0)
        printf("Token: %d (%s)\n", token, yytext);
    return 0;
}
*/
