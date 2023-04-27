#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define MAX_LEN 12 // 해시테이블의 identifier 최대 길이

typedef struct HTentry* HTpointer;
typedef struct HTentry {
	int index;  //index of identifier in ST
	HTpointer next;  //pointer to next identifier
} HTentry;

typedef enum errorTypes ERRORtypes;
enum tnumber tn;
ERRORtypes err;
//void symboltable(); symtable.c에 있던 main 대신 쓰려고 만든 함수. symtable.c에서 정의해야 할 거 같음. 그러나 과제 설명(lex실습 3 ppt) 보면 identifier가 심볼테이블에 들어오는 경우에 scanner.l에서 관리하라고 쓰여있는데 이걸 어떻게 구현해야 할지 모르겠음.
void printError(ERRORtypes err); // 'reporterror.c'파일에 위치한 함수. scanner.l에서 token match되었을 때 이용
void reportError(char* string); //'reporterror.c'파일에 위치한 함수. scanner.l에서 token match되었을 때 이용
void printToken(tn);
extern int errcnt;//에러 개수
extern yylex(); // 이 부분 때문에 에러나는 건 lex.yy.c 없어서 그런 것임
extern char* yytext; // 이 부분 때문에 에러나는 건 lex.yy.c 없어서 그런 것임