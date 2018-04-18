#include <iostream>
#include <windows.h>
#include "MutexLock.h"
using namespace std;

CMyMutex        MyMutex;	/*����һ��ȫ�ֵĻ����������Լ���װ�ģ�*/

DWORD WINAPI Fun(LPVOID lpParamter)
{
	string strPrint((const char*)lpParamter);
	int iRunTime = 0;
	while (++iRunTime<100)
	{
		/*����CMyMutex�Ĺ��캯�������������ֱ�ȡ�����͹رջ�����
		����CAutoLock�Ĺ������������ȥWaitForSingleObject��ReleaseMutex������
		*/
		CMutexLock cLock(&MyMutex);
		cout << "[" << iRunTime << "]:" << strPrint.c_str() << endl;
		//�̺߳�������������CPUʹ��Ȩ��
		Sleep(10);
	}
	return 0;
}

int main()
{
	//�������߳�
	string str1 = "A";
	string str2 = "B";
	string str3 = "C";
	string str4 = "D";
	string str5 = "E";

	HANDLE hThread1 = CreateThread(NULL, 0, Fun, (void*)str1.c_str(), 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, Fun, (void*)str2.c_str(), 0, NULL);
	HANDLE hThread3 = CreateThread(NULL, 0, Fun, (void*)str3.c_str(), 0, NULL);
	HANDLE hThread4 = CreateThread(NULL, 0, Fun, (void*)str4.c_str(), 0, NULL);
	HANDLE hThread5 = CreateThread(NULL, 0, Fun, (void*)str5.c_str(), 0, NULL);

	//�ر��߳�
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(hThread3);
	CloseHandle(hThread4);
	CloseHandle(hThread5);

	getchar();
	//  system("pause");
	return 0;
}