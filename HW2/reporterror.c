//����ó���ϴ� �κ� �ִ� c����. ppt���� ���û����̶�� �Ǿ��־����� ������ ���Ϸ� �и�����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"
errcnt = 0;

/* ���� ����
overfl: �ؽ����̺� �����÷ο� �߻�
illid_long: identifier ���̰� 12���� �̻�
illsp: �����ڰ� �ƴ� ��ȣ�� ���ԵǾ� ����
illid_digit: ���ڷ� ������*/
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
	if (strlen(string) > 12) {//�� �κ� �ʿ� ���� �� ������ ���ּ���
		err = illid_long;
		printerror(err);
	}

	else {
		//else�� identifier�� �ش�
		//symboltable ������ �Ѿ��
	}
}