#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

#define PRINT_TOKEN(type, stidx, token) printf("%-15s %-15s %-15s \n", type, stidx, token)
int numLine = 1;

void printToken(enum tnumber tn) { // 각 토큰 타입에 따라 적절히 print

	printf("%-15d", numLine);

	switch (tn) {
		//Comment
	case TCOMMENT: PRINT_TOKEN("single Comment line", "", "//Comment");  break;
	case TCOMMENTS: PRINT_TOKEN("multiple comment lines", "", "/*Comment*/"); 						int i;
		for (i = 0; i < yyleng; i++) {
			if (yytext[i] == '\n') {
				numLine++;
				printf(numLine);
				PRINT_TOKEN("multiple comment lines", "", "/*Comment*/");
			}
		}
		break;

		//Identifier & Constant
	case TIDENT: printf("%-15s %-15d %-15s \n", "Identifier", stIndex, yytext); break;
	case TEXIST:printf("%-15s %-15s %-15s \n", "Identifier", "already existed", yytext); break;
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
	printf("%-15s %-15s %-15s %-15s \n", "Line number", "Token type", "ST-index", "Token");
	while ((tn = yylex()) != TEOF) {
		printToken(tn);
	}
	if (cError == 0) printf("No errors detected");
	else printf("%d errors detected\n", cError);
	printf("\n\n");
}