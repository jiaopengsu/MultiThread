//��ʾ��������֤�ֶ���λ���Զ���λ�������Լ� SetEvent �� ResetEvent ��ʹ��

#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	HANDLE hEvent = CreateEvent(NULL       /*��ȫ����ָ��*/
		, false		                   /*��λ��ʽΪ�Զ�*/
		, true				           /*��ʼ��״̬*/
		, NULL                         /*�¼�����*/
	);

	WaitForSingleObject(hEvent, INFINITE);
	printf("A\n");

	WaitForSingleObject(hEvent, INFINITE);
	printf("B\n");

	SetEvent(hEvent);
	WaitForSingleObject(hEvent, INFINITE);
	printf("C\n");

	ResetEvent(hEvent);
	WaitForSingleObject(hEvent, INFINITE);
	printf("D\n");

	getchar();
	// SYSTEM("pause");
	return 0;
}

