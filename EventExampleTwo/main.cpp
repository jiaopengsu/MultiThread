// MultiThread.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <windows.h>
#include "EventLock.h"
using namespace std;

CMyEvent g_MyEvent; //事件

DWORD WINAPI Fun(LPVOID lpParamter)
{
	//CEventAutoLock clock(&g_MyEvent);
	string strPrint((const char*)lpParamter);

	int iRunTime = 0;
	while (++iRunTime < 10)
	{
		{
			CEventAutoLock clock(&g_MyEvent);
			cout << "线程[" << strPrint.c_str() << "]: " << "[" << iRunTime << "]" << endl;
		}
	}
	return 0;
}

int main()
{
	//创建五个子线程
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

	//关闭线程
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(hThread3);
	CloseHandle(hThread4);
	CloseHandle(hThread5);

	getchar();
	// SYSTEM("pause");
	return 0;
}

