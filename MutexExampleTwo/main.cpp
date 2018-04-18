#include <iostream>
#include <windows.h>
#include "MutexLock.h"
using namespace std;

CMyMutex        MyMutex;	/*声明一个全局的互斥量对象（自己封装的）*/

DWORD WINAPI Fun(LPVOID lpParamter)
{
	string strPrint((const char*)lpParamter);
	int iRunTime = 0;
	while (++iRunTime<100)
	{
		/*利用CMyMutex的构造函数和析构函数分别取创建和关闭互斥量
		利用CAutoLock的构造和析构函数去WaitForSingleObject和ReleaseMutex互斥量
		*/
		CMutexLock cLock(&MyMutex);
		cout << "[" << iRunTime << "]:" << strPrint.c_str() << endl;
		//线程函数阻塞，交出CPU使用权限
		Sleep(10);
	}
	return 0;
}

int main()
{
	//创建子线程
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
	//  system("pause");
	return 0;
}