#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define MAX_LEN 12 // �ؽ����̺��� identifier �ִ� ����

typedef struct HTentry* HTpointer;
typedef struct HTentry {
	int index;  //index of identifier in ST
	HTpointer next;  //pointer to next identifier
} HTentry;

typedef enum errorTypes ERRORtypes;
enum tnumber tn;
ERRORtypes err;
//void symboltable(); symtable.c�� �ִ� main ��� ������ ���� �Լ�. symtable.c���� �����ؾ� �� �� ����. �׷��� ���� ����(lex�ǽ� 3 ppt) ���� identifier�� �ɺ����̺� ������ ��쿡 scanner.l���� �����϶�� �����ִµ� �̰� ��� �����ؾ� ���� �𸣰���.
void printError(ERRORtypes err); // 'reporterror.c'���Ͽ� ��ġ�� �Լ�. scanner.l���� token match�Ǿ��� �� �̿�
void reportError(char* string); //'reporterror.c'���Ͽ� ��ġ�� �Լ�. scanner.l���� token match�Ǿ��� �� �̿�
void printToken(tn);
extern int errcnt;//���� ����
extern yylex(); // �� �κ� ������ �������� �� lex.yy.c ��� �׷� ����
extern char* yytext; // �� �κ� ������ �������� �� lex.yy.c ��� �׷� ����