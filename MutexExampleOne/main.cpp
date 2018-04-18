#include <iostream>
#include <windows.h>
using namespace std;

HANDLE hMutex = NULL;

DWORD WINAPI Fun(LPVOID lpParamter)
{
	string strPrint((const char*)lpParamter);

	DWORD dRes = -1;
	dRes = WaitForSingleObject(hMutex, INFINITE);
	if (WAIT_OBJECT_0 == dRes)
	{
		cout << "上锁成功!" << endl;
	}

	ReleaseMutex(hMutex);
	return 0;
}

int main()
{
	hMutex = CreateMutex(NULL            /*默认安全属性*/
		, false									/*创建线程不拥有该信号量*/
		, NULL									/*锁名称*/
	);

	DWORD dRes = -1;
	dRes = WaitForSingleObject(hMutex, INFINITE);
	if (WAIT_OBJECT_0 == dRes)
	{
		cout << "上锁成功!" << endl;
	}

	string str1 = "A";
	HANDLE hThread1 = CreateThread(NULL, 0, Fun, (void*)str1.c_str(), 0, NULL);

	ReleaseMutex(hMutex);
	dRes = WaitForSingleObject(hMutex, INFINITE);
	if (WAIT_OBJECT_0 == dRes)
	{
		cout << "上锁成功!" << endl;
	}
	CloseHandle(hMutex);
	getchar();
	//  system("pause");
	return 0;
}