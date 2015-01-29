%{

#include <stdio.h>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include "src/compiler.c"

int yylex(void);
extern int yylineno;

int yyerror(const char *error) {
	printf("ERROR: Line %d - %s\n", yylineno, error);
	exit(-3); return 0;
}

%}

%union {
	char *num;
	char *identifier;
	char *value;
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
	assign_variable($<identifier>1);
}|IF condition THEN commands ENDIF  {
	_if_handler();
}|IF condition THEN commands {
	end_of_ELSEIF();
} ELSE {
	_if_handler();
} commands ENDIF {
	_else_handler();

}|WHILE {
	_start_loop();
} condition DO commands ENDWHILE {
	_end_loop();
}|GET identifier SEM {
	get_variable($<identifier>2);
}|PUT value SEM {
	put_variable($<identifier>2);
};

expression:
value {
	_expression($<value>1);
}|value PLUS value {
	plus_expression($<value>1, $<value>3);
}|value MINUS value {
	minus_expression($<value>1, $<value>3);
}|value TIMES value {
	times_expression($<value>1, $<value>3);
}|value DIV value {
	div_expression($<value>1, $<value>3);
}|value MOD value {
	mod_expression($<value>1, $<value>3);
};

condition:
value EQ value {
	eq_condition($<value>1, $<value>3);
}|value DIFF value {
	diff_condition($<value>1, $<value>3);
}|value LE value {
	le_condition($<value>1, $<value>3);
}|value GE value {
	le_condition($<value>3, $<value>1);
}|value LEQ value {
	geq_condition($<value>3, $<value>1);
}|value GEQ value {
	geq_condition($<value>1, $<value>3);
};

value:
num {

}|identifier {

};
%%
