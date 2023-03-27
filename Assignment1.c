#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "testdata.txt"
#define STsize 1000 //size of string table
#define HTsize 100 //size of hash table
// more define variables��
//김제인 - 추가 매크로 함수 정의
#define isLetter(x) (((x) >= 'a' && (x) <= 'z') || ((x) >= 'A' && (x) <= 'Z') || (x) == '_')
#define isDigit(x) ((x) >= '0' && (x) <= '9')

typedef struct HTentry* HTpointer;
typedef struct HTentry {
	int index; //index of identifier in ST
	HTpointer next; //pointer to next identifier
} HTentry;

enum errorTypes { noerror, illsp, illid, overst };
typedef enum errorTypes ERRORtypes;

char separators[] = " .,;:?!\t\n";

HTpointer HT[HTsize];
char ST[STsize];

// more global variables��
ERRORtypes err;
//변수 추가 정의
int hash_code; // 식별자 해시코드
int found; // 식별자가 이미 존재하는 경우를 위한 flag
int same; // 식별자의 첫번째 인덱스(starting index)

FILE* fp; //to be a pointer to FILE
char input;


//Initialize - open input file

void initialize()
{
	fp = fopen(FILE_NAME, "r");
	input = fgetc(fp);
}


//김제인
// Skip Seperators - skip over strings of spaces,tabs,newlines, . , ; : ? !
// if illegal seperators,print out error message.

void SkipSeparators()
{
	char *ptr = strchr(separators, input);

	// 파일 탐색 중인데 문자도 숫자도 아닌 입력인 경우
	while(input != EOF && (isLetter(input) || isDigit(input)))
	{
		// 정의된 구분자도 아닌 경우
		if (ptr == NULL)
		{
			err = illsp;
			PrintError(err);
		}
		input = fgetc(fp); // 다음 글자로 반복
	} // 문자, 숫자면 while문 탈출
}


//소현아
// PrintHStable - Prints the hash table.write out the hashcode and the list of identifiers
// associated with each hashcode,but only for non-empty lists.
// Print out the number of characters used up in ST.

int PrintHStable(int sum)
{
	printf("[[HASH TABLE]]\n\n");
	for (int h = 0; h < HTsize; h++) {
		if (HT[h] == NULL) //HT 비어있을때
			continue;
		else { //HT 비어있지않을때
			printf("Hash Code %d : ",h); //Hash Code x : 까지 출력
			HTentry K = *HT[h];
			int HInd = K.index;
			while (ST[HInd] != '\0') { //index로 접근해 identifier끝까지 출력
				printf("%c", ST[HInd]);
				HInd++;
				sum++;
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
	return sum;
}


//강승연
// PrintError - Print out error messages
// overst : overflow in ST
// print the hashtable and abort by calling the function "abort()".
// illid : illegal identifier
// illsp :illegal seperator

void PrintError(ERRORtypes err)
{
}


//김제인
//ReadIO - Read identifier from the input file the string table ST directly into
// ST(append it to the previous identifier).
// An identifier is a string of letters and digits, starting with a letter.
// If first letter is digit, print out error message.

void ReadID()
{
}


//김혜진
// ComputeHS - Compute the hash code of identifier by summing the ordinal values of its
// characters and then taking the sum modulo the size of HT.
void ComputeHS(int nid, int nfree)
{
	int c = 0; // ���� ���� �� �ִ� ����
	int i;
	for (i = nid; i < nfree - 1; i++)
		c += (int)ST[i]; // �ݺ��� �̿��ؼ� �� ���� �� ���ϱ�
	hash_code = c % HTsize; // �ؽ����̺� ũ��� ����� �ؽ��ڵ� ���
}


//김혜진
// LookupHS -For each identifier,Look it up in the hashtable for previous occurrence
// of the identifier.If find a match, set the found flag as true.
// Otherwise flase.
// If find a match, save the starting index of ST in same id.

void LookupHS(int nid, int hscode)
{
}


//강승연
// ADDHT - Add a new identifier to the hash table.
// If list head ht[hashcode] is null, simply add a list element with
// starting index of the identifier in ST.
// IF list head is not a null , it adds a new identifier to the head of the chain

void ADDHT(int hscode)
{
	HTpointer htp; //구조체 변수 선언
	int i, j;

	found = 0; // 식별자가 나오지 않은 상태
	if (HT[hscode] != NULL) { // 비어있지 않은 경우
		htp = HT[hscode];
		while (htp != NULL && found == 0) {
			found = 1; // flag를 true로 설정
			i = htp->index;
			j = nid;
			same = i; // 해당 인덱스를 저장

			while (ST[i] != '\0' && ST[j] != '\0' && found == 1) { // 해시테이블 끝까지 각 식별자 비교하면서 겹치는 것 찾기

				if (ST[i] != ST[j])
					found = 0; // 식별자가 또 나오지 않은 것이므로 flag를 false로 설정

				else {
					i += 1;
					j += 1; // 이중 while문 반복 위해
				}
			}
			htp = htp->next;
		}
	}
}


//소현아
// MAIN - Read the identifier from the file directly into ST.
/*Compute its hashcode.
Look up the idetifier in hashtable HT[hashcode]
If matched, delete the identifier from STand print ST - index
of the matching identifier.
If not matched, add a new element to the list, pointing to new identifier.
Print the identifier, its index in ST, and whether it was entered or present.
Print out the hashtable, and number of characters used up in ST
*/

void PrintHeading()
{
	printf("-----------          ----------\n");
	printf("Index in ST          identifier\n");
	printf("-----------          ----------\n");
}

int main()
{
	int i; //?
	int sum = 0;

	PrintHeading();
	initialize();

	while (input != EOF) {
		err = noerror;
		SkipSeparators();
		ReadID();
		/*
		//(강승연)선언되지 않은 변수 사용으로 인한 에러 발생 - 주석처리
		
		if (input != EOF && err != illid) {
			if (nextfree == STsize) { 
				// print error message
			}

			ST[nextfree++] = '\0';
			ComputeHS(nextid, nextfree);
			LookupHS(nextid, hashcode);

			if (!found) {
				// print message
				ADDHT(hashcode);
			}
			else {
				// print message
			}
		}
		*/
	}
	PrintHStable(sum);
	printf("< %d characters are used in the string table >",sum);
}