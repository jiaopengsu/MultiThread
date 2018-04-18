#include <iostream>
#include <windows.h>
#include "MutexLock.h"

using namespace std;

CMyMutex::CMyMutex()
{
	m_hMutex = CreateMutex(NULL               /*默认安全属性*/
		, false               /*创建线程不拥有该信号量*/
		, NULL                /*锁名称*/
	);
}

CMyMutex::~CMyMutex()
{
	if (NULL != m_hMutex)
	{
		CloseHandle(m_hMutex);
		cout << "m_hMutex被关闭" << endl;
	}
}

void CMyMutex::Lock()
{
	if (NULL == m_hMutex)
	{
		cout << "m_hMutex为空" << endl;
		return;
	}
	DWORD dRes = -1;
	dRes = WaitForSingleObject(m_hMutex, INFINITE);
	if (WAIT_OBJECT_0 == dRes)
	{
		//      cout<<"上锁成功!"<<endl;
	}
	else if (WAIT_ABANDONED == dRes)
	{
		cout << "发生锁死现象" << endl;
	}
	else if (WAIT_TIMEOUT == dRes)
	{
		cout << "等待超时" << endl;
	}
	else if (WAIT_FAILED == dRes)
	{
		cout << "发生错误" << endl;
	}
	else
	{
		cout << "上锁失败!" << endl;
	}

}

void CMyMutex::UnLock()
{
	ReleaseMutex(m_hMutex);
}

//****************************CAutoLock*****************************************
CMutexLock::CMutexLock(CMyMutex* pMutex)
{
	m_pMutex = pMutex;
	m_pMutex->Lock();
}

CMutexLock::~CMutexLock()
{
	m_pMutex->UnLock();
}