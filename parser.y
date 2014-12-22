%{
	#define YYSTYPE int
	#include <stdio.h>
	#include <math.h>
	#include <string.h>
	#include <stdbool.h>

	int num_top = 0;
	int num_stack[2]; // unary and binary operations 
	char result[2048];
	bool error = false;

	int yylex(void);
	int yyerror(char *s);
	// extern yyyin;
	int calculator(int a, int b, char operator);
	int push(int number);
	void clean();
%}

%token NUMBER LBRACE RBRACE EOL ERROR

%left PLUS MINUS 
%left MUL DIV MOD
%right NEG
%right POW

%%

input:
	%empty
	| input line
;

line:
	EOL
	| exp EOL  {
		if(!error) {
			printf("%s\n", result);
			printf ("Wynik: %d\n", $1);
		} else {
			printf("undefined\n");
		}
		clean();
	}
	| error EOL	{
		printf("Błąd.\n");
	}
;

exp:
	NUMBER					{ $$ = push($1); }
	| exp PLUS exp			{ $$ = calculator($1, $3, '+'); }
	| exp MINUS exp			{ $$ = calculator($1, $3, '-'); }
	| exp MUL exp			{ $$ = calculator($1, $3, '*'); }
	| exp MOD exp			{
								if ($3 == 0) {
									error = true;
								} else {
									$$ = calculator($1, $3, '%');
								}
							}
	| exp DIV exp			{
								if ($3 == 0) {
									error = true;
								} else {
									$$ = calculator($1, $3, '/');
								}
							}
	| MINUS exp %prec NEG	{ $$ = push(-$2); }
	| exp POW exp			{ $$ = calculator($1, $3, '^'); } 
	| LBRACE exp RBRACE		{ $$ = $2; }
;

%%

int yyerror(char *s) {
	clean();
}

int push(int number) {
	if (number < 0) {
			num_stack[num_top] = number;
		} else {
			num_stack[++num_top] = number;
		}
	return number;
}

void num_print() {
	char str[128];

	for (int i = 1; i <= num_top; i++){
		sprintf(str, "%d ", num_stack[i]);
		strcat(result, str);
	}

	num_top = 0;
}

int calculator(int a, int b, char operator) {
	char str[16];
	num_print();
	
	switch(operator) {
		case '+':
			sprintf(str, "+ ");
			strcat(result, str);
			return a + b;
			break;

		case '-': 
			sprintf(str, "- ");
			strcat(result, str);
			return a - b;
			break;

		case '*':
			sprintf(str, "* ");
			strcat(result, str);
			return a * b;
			break;

		case '/':
			sprintf(str, "/ ");
			strcat(result, str);
			return a / b;
			break;

		case '%':
			sprintf(str, "%% ");
			strcat(result, str);
			return a % b;
			break;

		case '^':
			sprintf(str, "^ ");
			strcat(result, str);
			return (int) pow(a, b);
			break;
	}
	return 0;
}


void clean() {
	memset(&result[0], '\0', sizeof(result));
	error = false;
	num_top = 0;
}


int main(int argc, char **argv) {
	yyparse();
	printf("Bye.\n");
	return 0;
}
