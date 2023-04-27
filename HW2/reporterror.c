//에러처리하는 부분 있는 c파일. ppt에는 선택사항이라고 되어있었지만 별개의 파일로 분리했음
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"
errcnt = 0;

/* 에러 종류
overfl: 해시테이블에 오버플로우 발생
illid_long: identifier 길이가 12글자 이상
illsp: 구분자가 아닌 기호가 포함되어 있음
illid_digit: 숫자로 시작함*/
void printError(ERRORtypes err)
{
	if (err == overfl) {
		printf("***Error***\t\t overflow occured\n");
		errcnt++;
		exit(0);
	}
	else if (err == illid_long) {
		printf("***Error***\t\ttoo long identifier. It should be less than 12 letters\n");
	}
	else if (err == illsp) {
		printf("***Error***\t illegal separator is included \n");
	}
	else if (err == illid_digit) {
		printf("***Error***\t\t starts with digit\n");
	}
}

void reportError(char* string) {
	if (strlen(string) > 12) {//이 부분 필요 없을 거 같으면 빼주세요
		err = illid_long;
		printerror(err);
	}

	else {
		//else면 identifier에 해당
		//symboltable 관리로 넘어가게
	}
}