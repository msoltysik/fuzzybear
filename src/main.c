#include <stdio.h>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
extern FILE *yyin;
extern FILE *yyout;
extern int yyparse();

int main(int argc, char **argv) {
    ++argv, --argc;  /* skip over program name */
	
	if (argc == 1)
	{
		yyin = fopen(argv[0], "r");
		yyparse();
	} else {
		printf("Fuzzy Bear CC.\nCopyright (c) 2015.\nMateusz Sołtysik, JFTT @ WPPT.\n\n");
		printf("Usage:\n$ ./fuzzybear-cc in.imp\n");		
	}

	return 0;
}