#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define MAX_LEN 12 // 해시테이블의 identifier 최대 길이

enum errorTypes {
	noerror,
	illid_digit, //ident start with digit
	illid_long, //ident too long
	illid_illch, //ident illegal char
	overfl //overflow
};
typedef enum errorTypes ERRORtypes;

void SymbolTable();
void printError(ERRORtypes err); // 'reporterror.c'파일에 위치한 함수. scanner.l에서 token match되었을 때 이용

extern yylex(); // 이 부분 때문에 에러나는 건 lex.yy.c 없어서 그런 것임
extern char* yytext; // 이 부분 때문에 에러나는 건 lex.yy.c 없어서 그런 것임
extern int yyleng;
extern int numLine;
extern int stIndex;//ST-index
extern int cError;//error count
extern ERRORtypes err;