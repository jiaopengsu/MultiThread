#include <iostream>
#include <windows.h>
using namespace std;

HANDLE g_hSemaphore = NULL;                             //�����ź�������

unsigned long WINAPI Fun(LPVOID lpParamter)
{
	int iRunTime = 0;
	//ִ��100������
	while (++iRunTime < 100)
	{
		WaitForSingleObject(g_hSemaphore, INFINITE);      //�ź���ֵ-1
		cout << "Fun() is running!" << endl;
		ReleaseSemaphore(g_hSemaphore, 1, NULL);          //�ź���ֵ+1
		Sleep(10);
	}
	ExitThread(-1);
}

int main()
{
	//�����ź�������
	g_hSemaphore = CreateSemaphore(NULL          //�ź����İ�ȫ����
		, 1										 //�����ź����ĳ�ʼ�������������㵽���ֵ֮���һ��ֵ
		, 2                                      //�����ź�����������
		, NULL                                   //ָ���ź������������
	);

	if (NULL == g_hSemaphore)
	{
		cout << "create hSemaphore failed! error_code:" << GetLastError() << endl;
		return 0;
	}

	int iRunTime = 0;
	unsigned long ulThreadId = 0;
	//����һ�����߳�
	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, &ulThreadId);

	//ִ��100������
	while (++iRunTime < 100)
	{
		WaitForSingleObject(g_hSemaphore, INFINITE);   //�ź���ֵ-1
		cout << "main() is running, Thread id is " << ulThreadId << endl;

		//�ź���û���߳�����Ȩ���ԣ���һ���̻߳��ĳ���ź�����WaitForSingleObject���������ͷŸ��ź���֮ǰ��ReleaseSemaphore��
		//�������ٴν����ź������������򣨼��ٵ��� WaitForSingleObject ����������ʹ����ʣ���ź�����Դ��
		WaitForSingleObject(g_hSemaphore, INFINITE);   //�ź���ֵ-1
		cout << "main() is running, Thread id is " << ulThreadId << endl;

		ReleaseSemaphore(g_hSemaphore, 1, NULL);       //�ź���ֵ+1
		Sleep(10);
	}
	system("pause");

	return 0;
}


