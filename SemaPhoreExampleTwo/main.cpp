#include<string>
#include<iostream>
#include<process.h>
#include<windows.h>
using namespace std;
HANDLE hsem1, hsem2, hsem3;

//线程绑定的函数返回值和参数是确定的，而且一定要__stdcall
unsigned __stdcall threadFunA(void *)
{
	for (int i = 0; i < 10; i++) {
		WaitForSingleObject(hsem1, INFINITE);//等待信号量
		cout << "A";
		ReleaseSemaphore(hsem2, 1, NULL);//释放信号量
	}
	return 1;
}
unsigned __stdcall threadFunB(void *)
{
	for (int i = 0; i < 10; i++) {
		WaitForSingleObject(hsem2, INFINITE);//等待信号量
		cout << "B";
		ReleaseSemaphore(hsem3, 1, NULL);//释放信号量
	}
	return 2;
}
unsigned __stdcall threadFunC(void *)
{
	for (int i = 0; i < 10; i++) {
		WaitForSingleObject(hsem3, INFINITE);//等待信号量
		cout << "C" << endl;
		ReleaseSemaphore(hsem1, 1, NULL);//释放信号量
	}
	return 3;
}


int main()
{
	//创建信号量
	hsem1 = CreateSemaphore(NULL, 1, 1, NULL);
	hsem2 = CreateSemaphore(NULL, 0, 1, NULL);
	hsem3 = CreateSemaphore(NULL, 0, 1, NULL);

	HANDLE hth1, hth2, hth3;

	//创建线程
	hth1 = (HANDLE)_beginthreadex(NULL, 0, threadFunA, NULL, 0, NULL);
	hth2 = (HANDLE)_beginthreadex(NULL, 0, threadFunB, NULL, 0, NULL);
	hth3 = (HANDLE)_beginthreadex(NULL, 0, threadFunC, NULL, 0, NULL);

	//等待子线程结束
	WaitForSingleObject(hth1, INFINITE);
	WaitForSingleObject(hth2, INFINITE);
	WaitForSingleObject(hth3, INFINITE);

	//一定要记得关闭线程句柄
	CloseHandle(hth1);
	CloseHandle(hth2);
	CloseHandle(hth3);
	CloseHandle(hsem1);
	CloseHandle(hsem2);
	CloseHandle(hsem3);

	system("pause");
}