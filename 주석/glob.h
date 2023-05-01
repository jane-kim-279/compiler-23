/*
* global 변수 헤더 
*/
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

int SymbolTable();
void printError(ERRORtypes err); // 'reporterror.c'파일에 위치한 함수. scanner.l에서 error token match 되었을 때 이용

extern yylex(); 
extern char* yytext; 
extern int yyleng;
extern int numLine;//Line number 
extern int stIndex;//ST-index
extern int cError;//error count
extern ERRORtypes err;