/*
* global ���� ��� 
*/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define MAX_LEN 12 // �ؽ����̺��� identifier �ִ� ����


enum errorTypes {
	noerror,
	illid_digit, //ident start with digit
	illid_long, //ident too long
	illid_illch, //ident illegal char
	overfl //overflow
};
typedef enum errorTypes ERRORtypes;

int SymbolTable();
void printError(ERRORtypes err); // 'reporterror.c'���Ͽ� ��ġ�� �Լ�. scanner.l���� error token match �Ǿ��� �� �̿�

extern yylex(); 
extern char* yytext; 
extern int yyleng;
extern int numLine;//Line number 
extern int stIndex;//ST-index
extern int cError;//error count
extern ERRORtypes err;