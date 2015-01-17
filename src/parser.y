%{

#include <stdio.h>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include "src/compiler.c"

int yylex(void);
extern int yylineno;

int yyerror(const char *error) 
{ 
	printf("ERROR: Line %d - %s\n", yylineno, error);
	exit(-3); return 0;
}

%}

%union{
	char *num;
	char *identifier;
}
%token DECLARE IN END
%token ASSIGN IF THEN ENDIF ELSE WHILE DO ENDWHILE GET PUT
%token PLUS MINUS TIMES DIV MOD
%token EQ DIFF LE GE LEQ GEQ
%token <num> num
%token <identifier> identifier
%token <identifier> SEM

%%
program:
DECLARE vdeclarations IN commands END {
	end_of_file();
};

vdeclarations:
vdeclarations identifier {
	define_variable($<identifier>2);
}|{

};

commands:
commands command {

}|{

};

command:
identifier ASSIGN expression SEM {
	assign_variable($<identifier>1, $<identifier>3);
}|IF condition THEN commands ENDIF {

}|IF condition THEN commands ELSE commands ENDIF {

}|WHILE condition DO commands ENDWHILE {

}|GET identifier SEM {
	get_variable($<identifier>2);
}|PUT value SEM {
	put_variable($<identifier>2);
};

expression:
value {
	
}|value PLUS value {

}|value MINUS value {

}|value TIMES value {

}|value DIV value {

}|value MOD value {

};

condition:
value EQ value {

}|value DIFF value {

}|value LE value {

}|value GE value {

}|value LEQ value {

}|value GEQ value{

};

value:
num {

}|identifier {

};
%%
