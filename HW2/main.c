#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

//피피티에 있던 내용 그대로 넣어놓음
void main() {
	int numLine = 1;
	printf("Start\n\n");
	printf("Line number\tToken type\tST-index\tToken\n");
	while ((tn = yylex()) != TEOF) {
		printToken(tn);
	}
	if (errcnt == 0) printf("No errors detected");
	else printf("%d errors detected\n", errcnt);
	printf("\n\n");
}

