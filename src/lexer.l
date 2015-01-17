%option noyywrap
%option yylineno
%{
#include "bison.tab.h"
int yylex();

%}

%x IN_COMMENT

%%

<IN_COMMENT>"*)"	BEGIN(INITIAL);
<IN_COMMENT>.		;
<IN_COMMENT>"\n"    ;
"(*"		BEGIN(IN_COMMENT);
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
";"         return SEM;
[0-9]+		    {
		yylval.num = (char *) strdup(yytext);
     	return(num);
                }
[_a-z]+		   {
		yylval.identifier = (char *) strdup(yytext);
		return(identifier); 
                }
[ \t\n\r]		;
([_a-z]|[0-9])+ {
        printf("Błąd w linii %d: nierozpoznany napis %s\n", yylineno, yytext);
        exit(-1);
                }
.               {
        printf("Błąd w linii %d: niewłaściwy znak '%s'\n", yylineno, yytext);
        exit(-2);
                }
%%