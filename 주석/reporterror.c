/*
* 에러 출력 코드 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

int cError = 0; //에러 개수 count

/* 에러 종류
overfl: 해시테이블에 오버플로우 발생
illid_long: identifier 길이가 12글자 이상
illsp: 구분자가 아닌 기호가 포함되어 있음
illid_digit: 숫자로 시작함*/
void printError(ERRORtypes err)
{
	if (err == overfl) {
		printf("***Error***\t\t overflow occured\n");
		cError++;
		exit(0);
	}
	else if (err == illid_long) {
		printf("**Error**\t\t %s too long identifier \n",yytext);
		cError++;
	}
	else if (err == illid_illch) {
		printf("**Error**\t\t %s illegal chracter is included \n",yytext);
		cError++;
	}
	else if (err == illid_digit) {
		printf("**Error**\t\t starts with digit\n");
		cError++;
	}
}