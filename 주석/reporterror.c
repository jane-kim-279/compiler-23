/*
* ���� ��� �ڵ� 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

int cError = 0; //���� ���� count

/* ���� ����
overfl: �ؽ����̺� �����÷ο� �߻�
illid_long: identifier ���̰� 12���� �̻�
illsp: �����ڰ� �ƴ� ��ȣ�� ���ԵǾ� ����
illid_digit: ���ڷ� ������*/
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