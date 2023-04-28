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
void printError(ERRORtypes err); // 'reporterror.c'���Ͽ� ��ġ�� �Լ�. scanner.l���� token match�Ǿ��� �� �̿�

extern yylex(); // �� �κ� ������ �������� �� lex.yy.c ��� �׷� ����
extern char* yytext; // �� �κ� ������ �������� �� lex.yy.c ��� �׷� ����
extern int yyleng;
extern int numLine;
extern int stIndex;//ST-index
extern int cError;//error count
extern ERRORtypes err;