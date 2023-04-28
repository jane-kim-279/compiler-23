#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glob.h"

#define STsize 10000  //size of string table
#define HTsize 100	//size of hash table

#define FALSE 0
#define TRUE 1

#define isLetter(x) ( ((x) >= 'a' && (x) <='z') || ((x) >= 'A' && (x) <= 'Z' || (x) == '_') )
#define isDigit(x) ( (x) >= '0' && (x) <= '9' )

#define MAX_LEN		12

typedef struct HTentry* HTpointer;
typedef struct HTentry {
	int index;  //index of identifier in ST
	HTpointer next;  //pointer to next identifier
} HTentry;

char seperators[] = " .,;:?!\t\n";

HTpointer HT[HTsize];
char ST[STsize];

int nextid = 0;  //the current identifier
int nextfree = 0;  //the next available index of ST
int hashcode;  //hash code of identifier
int sameid;  //first index of identifier

int found;  //for the previous occurrence of an identifie

int stIndex = 0;

ERRORtypes err;

/*ReadIO 	- 	Read identifier from the input file the string table ST directly into
			ST(append it to the previous identifier).
			An identifier is a string of letters and digits, starting with a letter.
			If first letter is digit, print out error message. */
void ReadID()
{
	int count = 0;
	nextid = nextfree;
	if (isDigit(yytext[count])) {
		err = illid_digit;
		printError(err);
	}
	else {
		while (count < yyleng) {
			if (nextfree == STsize) {
				err = overfl;
				printError(err);
			}
			ST[nextfree++] = yytext[count];
			count++;
		}
	}
}

/* ComputeHS 	- 	Compute the hash code of identifier by summing the ordinal values of its
					characters and then taking the sum modulo the size of HT. */
void ComputeHS(int nid, int nfree)
{
	int code, i;
	code = 0;
	for (i = nid; i < nfree - 1; i++)
		code += (int)ST[i];
	hashcode = (code % HTsize) + 1;
	hashcode = (hashcode == HTsize ? 0 : hashcode);
}

/*LookupHS 	-	For each identifier,Look it up in the hashtable for previous occurrence
				of the identifier.If find a match, set the found flag as true.
				Otherwise flase.
				If find a match, save the starting index of ST in same id. */
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


/* ADDHT	-	Add a new identifier to the hash table.
			If list head ht[hashcode] is null, simply add a list element with
			starting index of the identifier in ST.
			IF list head is not a null , it adds a new identifier to the head of the chain */
void ADDHT(int hscode)
{
	HTpointer ptr;

	ptr = (HTpointer)malloc(sizeof(ptr));
	ptr->index = nextid;
	ptr->next = HT[hscode];
	HT[hscode] = ptr;
}

void SymbolTable() {

	int i;

	err = noerror;
	ReadID();
	if (err == noerror) {
		if (nextfree == STsize) {
			err = overfl;
			printError(err);
		}
		ST[nextfree++] = '\0';

		ComputeHS(nextid, nextfree);
		LookupHS(nextid, hashcode);

		stIndex = nextid;

		if (!found) {
			//printf("          (entered)\n");
			ADDHT(hashcode);
		}
		else {
			//printf("          (already existed)\n");
			nextfree = nextid;
		}
	}

}
