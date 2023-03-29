#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_NAME "./2023_testdata/testdata4.txt"

#define STsize 1000 //스트링 테이블 크기 나타내는 상수 선언
#define HTsize 100 //해시 테이블 크기 나타내는 상수 선언
#define TTsize 50 //ReadIID에서 사용하는 임시 테이블 크기 나타내는 상수 선언 (추가로 정의함)

#define FALSE 0
#define TRUE 1

#define isLetter(x) ( ((x) >= 'a' && (x) <= 'z') || ((x)>= 'A' && (x) <= 'Z') || (x) == '_')
#define isDigit(x) ((x)>= '0' && (x) <= '9') // 구분자인지 아닌지 알기 위해 사용

typedef struct HTentry* HTpointer;
typedef struct HTentry {
    int index;
    HTpointer next;
}HTentry;

enum errorTypes { noerror, illid, overst, overtwelve }; // 12자 넘는 것 제외하기 위해 overtwelve 추가 정의
typedef enum errorTypes ERRORtypes;

char seperators[] = " .,;:?!\t\n";

HTpointer HT[HTsize];
char ST[STsize];
char TempT[TTsize]; // 추가로 정의

int nextid = 0;
int nextfree = 0;

int hashcode;
int sameid; // 구분자 구하기 위한 변수들

int found;
int allowed;
char unallowedchar; // 문제에 제시된 기호 아닌 다른 기호 에러 처리 위해 정의한 변수

ERRORtypes err;

FILE* fp;
char input;


//초기화 (파일 읽기 위해)
void initialize()
{
    fp = fopen(FILE_NAME, "r");
    input = fgetc(fp);
}


//구분자 찾아내기 위해 새롭게 정의한 함수
int isSeperator(char c)
{
    int i;
    int sep_len;

    sep_len = strlen(seperators);
    for (i = 0; i < sep_len; i++) {
        if (c == seperators[i])
            return 1;
    }
    return 0;
}



//헤더 출력 함수
void PrintHeading()
{
    printf("\n\n");
    printf(" ----------    ---------- \n");
    printf(" Index in ST   identifier \n");
    printf(" ----------    ---------- \n");
    printf("\n");
}


//헤시테이블 출력
void PrintHStable()
{
    int HInd;
    printf("\n\n[[HASH TABLE]]\n\n");
    for (int h = 0; h < HTsize; h++) {
        if (HT[h] == NULL) //HT 비어있을때
            continue;
        else { //HT 비어있지않을때
            printf("Hash Code %3d : ", h); //Hash Code x : 까지 출력
            HTentry K = *HT[h];
            int HInd = K.index;
            while (ST[HInd] != '\0') { //index로 접근해 identifier끝까지 출력
                printf("%c", ST[HInd]);
                HInd++;
            }
            while (K.next != NULL) { //HTentry의 다음 pointer가 null일때까지 반복
                printf("   ");
                K = *(K.next);
                HInd = K.index;
                while (ST[HInd] != '\0') {
                    printf("%c", ST[HInd]);
                    HInd++;
                }
            }
            printf("\n");
        }
    }
    printf("\n\n< %d characters are used in the string table >\n", nextfree);
}


//에러 출력 함ㅅ수
void PrintError(ERRORtypes err)
{
    switch (err) {
    case overst:
        printf("...Error...       OVERFLOW"); //오버플로우된 경우
        PrintHStable();
        exit(0);
        break;

    case illid:  // 숫자로 시작하는 경우
        printf("...Error...     ");
        while (input != EOF && (isLetter(input) || isDigit(input))) {
            printf("%c", input);
            input = fgetc(fp);
        }
        printf("           start with digit \n");
        break;

    case overtwelve: // 열두 글자 초과하는 경우
        printf("...Error... ");
        for (int i = nextid; i < nextfree - 1; i++)
            printf("%c", ST[i]);
        printf("         too long identifier \n");
        break;
    }
}



// 구분자일 경우 그냥 넘어가고 아닐 경우 에러 처리(illspr)하는 함수였으나 printerror 호출하지 않고 main에서 출력하는 걸로 바꿈
void SkipSeperators()
{
    char* ptr = strchr(seperators, input);

    while (input != EOF && !(isLetter(input) || isDigit(input))) {
        if (!isSeperator(input)) {//구분자도 아닐때
            break;
        }
        input = fgetc(fp);
    }
}



//파일에서 문자 읽어온 후 ST에 집어넣는 함수. LookupHS 함수와 구성 비슷함
void ReadID()
{
    int i = 0;
    allowed = 0; // flag
    nextid = nextfree;
    if (isDigit(input)) {
        err = illid;
        PrintError(err);
    }
    else {
        while (input != EOF && !isSeperator(input)) {
            if (!(isLetter(input) || isDigit(input))) {
                unallowedchar = input;
                allowed = 1;
            }
            TempT[i] = input;
            i++;
            input = fgetc(fp);
        }

        if (allowed == 0) {
            for (int j = 0; j < i; j++) {
                if (nextfree == STsize) {
                    err = overst;
                    PrintError(err); // 오버플로우에 대한 에러 처리 위해 함수 호출
                }
                ST[nextfree++] = TempT[j]; //Tempt 이용해서 사용 가능한 구분자 사용한 것만 ST에 담음
            }
        }
        else allowed = i;
    }
}




//해시테이블 계산
void ComputeHS(int nid, int nfree)
{
    int code, i;
    code = 0;
    for (i = nid; i < nfree - 1; i++)
        code += tolower(ST[i]);
    hashcode = code % HTsize; // 각 값을 더해서 테이블 크기로 나눔
}





// 중복값 있는지 확인하는 함수
void LookupHS(int nid, int hscode)
{
    HTpointer here;
    int i, j;

    found = FALSE;
    if (HT[hscode] != NULL) {
        here = HT[hscode];
        while (here != NULL && found == FALSE) {
            found = TRUE;
            i = here->index; // 해시테이블 포인터의 인덱스 접근: 인덱스 이용하여 테이블 내에 있는 다른 값과 비교
            j = nid;
            sameid = i;

            while (ST[i] != '\0' && ST[j] != '\0' && found == TRUE) {
                if (toupper(ST[i]) != toupper(ST[j])) { // toupper 함수 이용하여 대소문자 무시
                    found = FALSE;
                }
                else {
                    i++;
                    j++;
                }
            }
            here = here->next;
        }
    }
}




//해시테이블에 새로운 값 추가
void ADDHT(int hscode)
{
    HTpointer ptr;

    ptr = (HTpointer)malloc(sizeof(ptr)); // 구조체 동적 할당
    ptr->index = nextid; // 구분자 값
    ptr->next = HT[hscode];
    HT[hscode] = ptr; // 최종적으로 해시테이블에 추가
}



//메인 함수: 위에서 만든 사용자정의 함수를 조합하고 허용되지 않는 구분자라는 에러, 오버플로우 에러 출력
int main() {
    int i;
    PrintHeading();
    initialize();

    while (input != EOF) {
        err = noerror;
        SkipSeperators();
        if (input != EOF) {
            ReadID();
            if (allowed != 0)
            {
                printf("...Error...   ");
                for (i = 0; i < allowed; i++)
                    printf("%c", TempT[i]);
                printf("  %c Is not allowed\n", unallowedchar);
                continue;
            }

            if (err != illid) {
                if (nextfree == STsize) {
                    err = overst;
                    PrintError(err);
                }
                ST[nextfree++] = '\0';

                ComputeHS(nextid, nextfree);
                LookupHS(nextid, hashcode);

                if (!found) {
                    if (nextfree - nextid > 12) {
                        err = overtwelve;
                        PrintError(err); // 열두글자 이상인 경우
                    }

                    else {
                        printf("%6d         ", nextid);
                        for (i = nextid; i < nextfree - 1; i++)
                            printf("%c", ST[i]);
                        printf("     (entered)\n");
                        ADDHT(hashcode);
                    }

                }
                else {
                    printf("%6d         ", sameid);
                    for (i = nextid; i < nextfree - 1; i++)
                        printf("%c", ST[i]);
                    printf("     (already existed)\n");
                    nextfree = nextid;
                }
            }
        }
    }
    PrintHStable();
}
