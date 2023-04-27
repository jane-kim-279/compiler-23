//printToken 함수가 길어져서 별개의 c 파일로 분리함
#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
enum tnumber tn; //token type
int numLine = 0; //line number

void printToken(tn) { // 각 토큰 타입에 따라 적절히 print

	if (tn == TSEPARATOR) (void)0;
	else {
		switch (tn) {
		case TCONST: printf("Constant\t"); break;
		case TELSE: printf("Else\t"); break;
		case TIF: printf("If\t"); break;
		case TINT: printf("Integer\t"); break;
		case TRETURN: printf("Return\t"); break;
		case TVOID: printf("Void\t"); break;
		case TWHILE: printf("While\t"); break;

		case TPLUS: printf("Add\t"); break;
		case TMINUS: printf("Subract\t"); break;
		case TSTAR: printf("Multiply\t"); break;
		case TSLASH: printf("Divide\t"); break;
		case TMOD: printf("Mod\t"); break;

		case TASSIGN: printf("Assign\t"); break;
		case TADDASSIGN: printf("Add and assign\t"); break;
		case TSUBASSIGN: printf("Subtract and assign\t"); break;
		case TMULASSIGN: printf("Multiply and assign\t"); break;
		case TDIVASSIGN: printf("Divide and assign\t"); break;
		case TMODASSIGN: printf("Mod and assign\t"); break;

		case TAND: printf("And\t"); break;
		case TOR: printf("Or\t"); break;

		case TEQUAL: printf("Equal\t"); break;
		case TNOTEQU: printf("Not_Equal\t"); break;
		case TLESS: printf("Less\t"); break;
		case TGREAT: printf("Great\t"); break;
		case TLESSE: printf("Less equal\t"); break;
		case TGREATE: printf("Great equal\t"); break;

		case TINC: printf("Increase\t"); break;
		case TDEC: printf("Decrease\t"); break;

		case TSMALLBL: printf("Left Small Bracket\t"); break;
		case TSMALLBR: printf("Right Small Bracket\t"); break;
		case TBEGIN: printf("Left Medium Bracket\t"); break;
		case TEND: printf("Right Medium Bracket\t"); break;
		case TBIGBL: printf("Left Large Bracket\t"); break;
		case TBIGBR: printf("Right Large Bracket\t"); break;
		case TCOMMA: printf("Comma\t"); break;
		case TSEMI: printf("Semicolon\t"); break;

		case TSQUOTE: printf("Small Quote"); break;
		case TBQUOTE: printf("Big Quote"); break;

		case TIDENTIFIER: reportError(yytext); break; //인식한 identifier의 오류를 점검
		case TNUMBER: printf("Number: %d\t", atoi(yytext)); break;

		case TERROR: printError(illsp); break; //illegal symbol일 때 출력

		case TCOMMENT: printf("single Comment line\t");  break;
		case TCOMMENTS: printf("multiple comment lines\t");  countline(yytext); break; //여러 줄 주석의 라인 개수 출력
		}
		printf("\n");
	}
	
}
//라인 수 세는 함수
void countline(char* string)
{

	int i = 0;

	while (string[i] != '\0') {
		if (string[i] == '\n' || string[i] == '\r') numLine++;
		i++;
	}
}