#include<string>
#include<iostream>
#include<process.h>
#include<windows.h>
using namespace std;
HANDLE hsem1, hsem2, hsem3;

//�̰߳󶨵ĺ�������ֵ�Ͳ�����ȷ���ģ�����һ��Ҫ__stdcall
unsigned __stdcall threadFunA(void *)
{
	for (int i = 0; i < 10; i++) {
		WaitForSingleObject(hsem1, INFINITE);//�ȴ��ź���
		cout << "A";
		ReleaseSemaphore(hsem2, 1, NULL);//�ͷ��ź���
	}
	return 1;
}
unsigned __stdcall threadFunB(void *)
{
	for (int i = 0; i < 10; i++) {
		WaitForSingleObject(hsem2, INFINITE);//�ȴ��ź���
		cout << "B";
		ReleaseSemaphore(hsem3, 1, NULL);//�ͷ��ź���
	}
	return 2;
}
unsigned __stdcall threadFunC(void *)
{
	for (int i = 0; i < 10; i++) {
		WaitForSingleObject(hsem3, INFINITE);//�ȴ��ź���
		cout << "C" << endl;
		ReleaseSemaphore(hsem1, 1, NULL);//�ͷ��ź���
	}
	return 3;
}


int main()
{
	//�����ź���
	hsem1 = CreateSemaphore(NULL, 1, 1, NULL);
	hsem2 = CreateSemaphore(NULL, 0, 1, NULL);
	hsem3 = CreateSemaphore(NULL, 0, 1, NULL);

	HANDLE hth1, hth2, hth3;

	//�����߳�
	hth1 = (HANDLE)_beginthreadex(NULL, 0, threadFunA, NULL, 0, NULL);
	hth2 = (HANDLE)_beginthreadex(NULL, 0, threadFunB, NULL, 0, NULL);
	hth3 = (HANDLE)_beginthreadex(NULL, 0, threadFunC, NULL, 0, NULL);

	//�ȴ����߳̽���
	WaitForSingleObject(hth1, INFINITE);
	WaitForSingleObject(hth2, INFINITE);
	WaitForSingleObject(hth3, INFINITE);

	//һ��Ҫ�ǵùر��߳̾��
	CloseHandle(hth1);
	CloseHandle(hth2);
	CloseHandle(hth3);
	CloseHandle(hsem1);
	CloseHandle(hsem2);
	CloseHandle(hsem3);

	system("pause");
}