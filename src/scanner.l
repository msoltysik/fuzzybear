%option noyywrap
%option yylineno
%option c++


%{
	#include <iostream>
	#include <cstdlib>
	#include "parser.cpp"

	using namespace std;
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

[_a-z]+		   {
                 	return(identifier); 
                }
[0-9]+		    {
    				yylval.num = (char *)strdup(yytext);
                 	return(num);
                }

[ \t\n\r]       /* skip whitespace */

([_a-z]|[0-9])+ {
                    cout << "Błąd w linii" << yylineno << ": nierozpoznany napis " << YYText()  << endl;
                    exit(-1);
                }
.               {
                    cout << "Błąd w linii" << yylineno << ": niewłaściwy znak " << YYText()  << endl;
                    exit(-2);
                }
%%

int main( int /* argc */, char** /* argv */ )
 {
     FlexLexer* lexer = new yyFlexLexer;
     while(lexer->yylex() != 0)
         ;
     return 0;
 }
