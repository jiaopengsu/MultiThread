//此示例程序验证手动置位和自动置位的区别，以及 SetEvent 和 ResetEvent 的使用

#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	HANDLE hEvent = CreateEvent(NULL       /*安全属性指针*/
		, false		                   /*复位方式为自动*/
		, true				           /*初始化状态*/
		, NULL                         /*事件名称*/
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

