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
		cout << "�����ɹ�!" << endl;
	}

	ReleaseMutex(hMutex);
	return 0;
}

int main()
{
	hMutex = CreateMutex(NULL            /*Ĭ�ϰ�ȫ����*/
		, false									/*�����̲߳�ӵ�и��ź���*/
		, NULL									/*������*/
	);

	DWORD dRes = -1;
	dRes = WaitForSingleObject(hMutex, INFINITE);
	if (WAIT_OBJECT_0 == dRes)
	{
		cout << "�����ɹ�!" << endl;
	}

	string str1 = "A";
	HANDLE hThread1 = CreateThread(NULL, 0, Fun, (void*)str1.c_str(), 0, NULL);

	ReleaseMutex(hMutex);
	dRes = WaitForSingleObject(hMutex, INFINITE);
	if (WAIT_OBJECT_0 == dRes)
	{
		cout << "�����ɹ�!" << endl;
	}
	CloseHandle(hMutex);
	getchar();
	//  system("pause");
	return 0;
}