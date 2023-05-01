/*
* printToken() 와 main() 코드 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

#define PRINT_TOKEN(type, stidx, token) printf("%-20s %-15s %-15s \n", type, stidx, token)
int numLine = 1;

//토큰 타입에 따라 print 
void printToken(enum tnumber tn) { 

	printf("%-15d", numLine); //맨 앞에 Line number print

	switch (tn) {
		//Comment
	case TCOMMENT: PRINT_TOKEN("single Comment line", "", "//Comment");  break;
	case TCOMMENTS: PRINT_TOKEN("multiple comment lines", "", "/*Comment*/"); 					
		int i;
		for (i = 0; i < yyleng; i++) { //여러 줄 주석일 경우 \n 확인 후 Line number 수정 
			if (yytext[i] == '\n') {
				numLine++;
				printf(numLine);
				PRINT_TOKEN("multiple comment lines", "", "/*Comment*/");
			}
		}
		break;

		//Identifier & Constant
	case TIDENT: printf("%-20s %-15d %-15s %-15s\n", "Identifier", stIndex, yytext, "(entered)"); break;
	case TEXIST:printf("%-20s %-15d %-15s %-15s\n", "Identifier", stIndex, yytext ,"(already existed)" ); break; 
	case TDNUMBER: PRINT_TOKEN("Decimal Number", "", yytext); break;
	case TONUMBER: PRINT_TOKEN("Octal Number", "", yytext); break;
	case THNUMBER: PRINT_TOKEN("Hexadecimal Number", "", yytext); break;

		//Keyword - const, else, if, int, return, void, while
	case TCONST: PRINT_TOKEN("Constant", "", yytext); break;
	case TELSE: PRINT_TOKEN("Else", "", yytext); break;
	case TIF: PRINT_TOKEN("If", "", yytext); break;
	case TINT: PRINT_TOKEN("Integer", "", yytext); break;
	case TRETURN: PRINT_TOKEN("Return", "", yytext); break;
	case TVOID: PRINT_TOKEN("Void", "", yytext); break;
	case TWHILE: PRINT_TOKEN("While", "", yytext); break;

		//Operator 1 - Arithmetic operator - +, -, *, /, %
	case TPLUS: PRINT_TOKEN("Add", "", yytext); break;
	case TMINUS: PRINT_TOKEN("Subract", "", yytext); break;
	case TSTAR: PRINT_TOKEN("Multiply", "", yytext); break;
	case TSLASH: PRINT_TOKEN("Divide", "", yytext); break;
	case TMOD: PRINT_TOKEN("Mod", "", yytext); break;

		//Operator 2 - Assign operator - =, +=, -=, *=, /=, %=
	case TASSIGN: PRINT_TOKEN("Assign", "", yytext); break;
	case TADDASSIGN: PRINT_TOKEN("Add and assign", "", yytext); break;
	case TSUBASSIGN: PRINT_TOKEN("Subtract and assign", "", yytext); break;
	case TMULASSIGN: PRINT_TOKEN("Multiply and assign", "", yytext); break;
	case TDIVASSIGN: PRINT_TOKEN("Divide and assign", "", yytext); break;
	case TMODASSIGN: PRINT_TOKEN("Mod and assign", "", yytext); break;

		//Operator 3 - Logic operator - !, &&, ||
	case TAND: PRINT_TOKEN("And", "", yytext); break;
	case TOR: PRINT_TOKEN("Or", "", yytext); break;
	case TNOT: PRINT_TOKEN("NOT", "", yytext); break;

		//Operator 4 - Relation operator - ==, !=, <, >, <=, >=
	case TEQUAL: PRINT_TOKEN("Equal", "", yytext); break;
	case TNOTEQU: PRINT_TOKEN("Not_Equal", "", yytext); break;
	case TLESS: PRINT_TOKEN("Less", "", yytext); break;
	case TGREAT: PRINT_TOKEN("Great", "", yytext); break;
	case TLESSE: PRINT_TOKEN("Less equal", "", yytext); break;
	case TGREATE: PRINT_TOKEN("Great equal", "", yytext); break;

		//Operator 5 - Increase & Decrease operator - ++, --
	case TINC: PRINT_TOKEN("Increase", "", yytext); break;
	case TDEC: PRINT_TOKEN("Decrease", "", yytext); break;

		//Special Symbols 1 - (, ), {, }, [, ]
	case TSMALLBL: PRINT_TOKEN("Left Small Bracket", "", yytext); break;
	case TSMALLBR: PRINT_TOKEN("Right Small Bracket", "", yytext); break;
	case TBEGIN: PRINT_TOKEN("Left Medium Bracket", "", yytext); break;
	case TEND: PRINT_TOKEN("Right Medium Bracket", "", yytext); break;
	case TBIGBL: PRINT_TOKEN("Left Large Bracket", "", yytext); break;
	case TBIGBR: PRINT_TOKEN("Right Large Bracket", "", yytext); break;

		//Special Symbols 2 - ,, ;
	case TCOMMA: PRINT_TOKEN("Comma", "", yytext); break;
	case TSEMI: PRINT_TOKEN("Semicolon", "", yytext); break;

		//Errors
	case TLONGIDENTERR: err = illid_long; printError(err);  break;
	case TILLIDENTERR: err = illid_digit; printError(err); break;
	case TILLCHARERR: err = illid_illch; printError(err); break;
	}

}

void main() {
	enum tokentypes tn;
	numLine = 1;
	printf("Start\n\n");
	printf("%-15s %-20s %-15s %-15s \n", "Line number", "Token type", "ST-index", "Token");
	while ((tn = yylex()) != TEOF) { 
		printToken(tn);
	}
	//에러 개수에 따른 출력 
	if (cError == 0) printf("No errors detected");
	else printf("%d errors detected\n", cError);
	printf("\n\n");
}