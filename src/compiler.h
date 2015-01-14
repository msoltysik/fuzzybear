#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {SECOND_DECLARATION, UNDECLARATED_VARIABLE, USING_OF_UNDECLARATED_VARIABLE} errors;

typedef struct {
	char* name;
	char* value;
} Variable;

typedef struct {
	Variable stack[9999];
	int top;	
} VariableStack;

VariableStack* variableStack;

void VariableStackInit()
{
	variableStack = (VariableStack*)malloc(sizeof(VariableStack));
	variableStack->top = 0;
}

void pushVariableStack(Variable variable)
{
	variableStack->stack[variableStack->top] = variable;
	variableStack->top++;
}

Variable popVariableStack()
{
	variableStack->top--;
	return variableStack->stack[variableStack->top + 1];
}

void VariableStackFree()
{
	free(variableStack);
}

void error_factory(errors error)
{
	switch (error) {
		case SECOND_DECLARATION:
			printf("%s\n", "dupa1");
			exit(-5);
		case UNDECLARATED_VARIABLE:
			printf("%s\n", "dupa1");
			exit(-5);
		case USING_OF_UNDECLARATED_VARIABLE:
			printf("%s\n", "dupa1");
			exit(-5);
	}
}

bool is_not_number(char* p)
{
	int len = strlen(p);
    for (int i = 0; i < len; i++) {
    	if (p[i] < 48 || p[i] > 57)
    	{
    		return true;
    	}
    }
	return false;
}


void define_variable(char* declaration)
{

}

void assign_variable(char* variable)
{

}

void get_variable(char* variable)
{

}

void put_variable(char* variable)
{

}

// Expressions
void plus_expression(char* variable1, char* variable2)
{
	printf("1: %s\n", variable1);
	if (is_not_number(variable1))
	{
		printf("Nie jest numerem\n");
	}
	printf("2: %s\n", variable2);
	if (is_not_number(variable2))
	{
		printf("Nie jest numerem\n");
	}

}

void minus_expression(char* variable1, char* variable2)
{
	
}

void times_expression(char* variable1, char* variable2)
{
	
}

void div_expression(char* variable1, char* variable2)
{

}

void mod_expression(char* variable1, char* variable2)
{
	
}


// Conditions

void eq_condition(char* variable1, char* variable2)
{
	
}

void diff_condition(char* variable1, char* variable2)
{
	
}

void le_condition(char* variable1, char* variable2)
{
	
}

void ge_condition(char* variable1, char* variable2)
{
	
}

void leq_condition(char* variable1, char* variable2)
{
	
}

void geq_condition(char* variable1, char* variable2)
{
	
}

// HALT
void end_of_program()
{

}

void init_cc()
{
	VariableStackInit();
}

void generate_cc()
{

}

void free_cc()
{
	VariableStackFree();
}