//�����Բ��� �÷��ֽ� ���� 1 �ڵ� �������� ���� ����
//printheading, printHStable ����: �̹� ���������� �ؽ����̺� ����� �ʿ� ���� �� ���Ƽ� ����
//�� �Ʒ��� Symboltable �Լ� ���� �ʿ�
#define HTsize 100
#define STsize 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

#define FILE_NAME "testdata.txt"

#define FALSE 0
#define TRUE 1

#define isLetter(x) ( ((x) >= 'a' && (x) <='z') || ((x) >= 'A' && (x) <= 'Z' || (x) == '_') )
#define isDigit(x) ( (x) >= '0' && (x) <= '9' )

char seperators[] = " .,;:?!\t\n";

int found = 0;
nid = 0;
sameid = 0;
nextfree = 0;
nextid = 0;
int hashcode;
err = noerror;

char ST[STsize];
HTpointer HT[HTsize];

FILE* fp;   //to be a pointer to FILE 
char input;

//Initialize - open input file
void initialize()
{
	fp = fopen(FILE_NAME, "r");
	input = fgetc(fp);
}

//isSerperator  -  distinguish the seperator
//Returns 1 if seperator, otherwise returns 0
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

void SkipSeperators()
{
	while (input != EOF && !(isLetter(input) || isDigit(input))) {
		if (!isSeperator(input)) {
			err = illid_illch;
			printError(err);
		}
		input = fgetc(fp);
	}
}


void ReadID()
{
	int count = 0;
	nextid = nextfree;
	if (isDigit(input)) {
		err = illid_digit;
		printError(err);
	}
	else {
		while (input != EOF && !isSeperator(input)) {
			if (nextfree == STsize) {
				err = overfl;
				printError(err);
			}
			ST[nextfree++] = input; // �� �κ� ���� ������ �߻��� �� ������ ������ �־ �׽�Ʈ ��Ź�帳�ϴ�
			input = fgetc(fp);
			count++;

			if (!(isLetter(input) || isDigit(input) || isSeperator(input)) && input != EOF) {
				err = illsp;
			}
		}
		if (count >= MAX_LEN) {
			err = illid_long;
			ST[nextfree] = '\0';
			printError(err);
			nextfree = nextid;
		}
		if (err == illsp) {
			ST[nextfree] = '\0';
			printError(err);
			nextfree = nextid;
		}
	}
}


void ComputeHS(int nid, int nfree)
{
	int code, i;
	code = 0;
	for (i = nid; i < nfree - 1; i++) {
		int current = (int)ST[i];
		//If current is lowercase, convert it to uppercase
		current = (current >= 'A' && current <= 'Z' ? current - 'A' + 'a' : current);
		code += current;
	}
	hashcode = (code % HTsize) + 1;
	hashcode = (hashcode == HTsize ? 0 : hashcode);
}


void LookupHS(int nid, int hscode)
{
	HTpointer here;
	int i, j;

	found = FALSE;
	if (HT[hscode] != NULL) {
		here = HT[hscode];
		while (here != NULL && found == FALSE) {
			found = TRUE;
			i = here->index;
			j = nid;
			sameid = i;

			while (ST[i] != '\0' && ST[j] != '\0' && found == TRUE) {
				int left = ST[i] >= 'A' && ST[i] <= 'Z' ? ST[i] - 'A' + 'a' : ST[i];
				int right = ST[j] >= 'A' && ST[j] <= 'Z' ? ST[j] - 'A' + 'a' : ST[j];
				if (left != right)
					found = FALSE;
				else {
					i++;
					j++;
				}
			}
			here = here->next;
		}
	}
}


void ADDHT(int hscode)
{
	HTpointer ptr;

	ptr = (HTpointer)malloc(sizeof(ptr));
	ptr->index = nextid;
	ptr->next = HT[hscode];
	HT[hscode] = ptr;
}

//Symboltable�Լ� ���� �ʿ�
