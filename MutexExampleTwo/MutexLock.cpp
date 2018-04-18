#include <iostream>
#include <windows.h>
#include "MutexLock.h"

using namespace std;

CMyMutex::CMyMutex()
{
	m_hMutex = CreateMutex(NULL               /*Ĭ�ϰ�ȫ����*/
		, false               /*�����̲߳�ӵ�и��ź���*/
		, NULL                /*������*/
	);
}

CMyMutex::~CMyMutex()
{
	if (NULL != m_hMutex)
	{
		CloseHandle(m_hMutex);
		cout << "m_hMutex���ر�" << endl;
	}
}

void CMyMutex::Lock()
{
	if (NULL == m_hMutex)
	{
		cout << "m_hMutexΪ��" << endl;
		return;
	}
	DWORD dRes = -1;
	dRes = WaitForSingleObject(m_hMutex, INFINITE);
	if (WAIT_OBJECT_0 == dRes)
	{
		//      cout<<"�����ɹ�!"<<endl;
	}
	else if (WAIT_ABANDONED == dRes)
	{
		cout << "������������" << endl;
	}
	else if (WAIT_TIMEOUT == dRes)
	{
		cout << "�ȴ���ʱ" << endl;
	}
	else if (WAIT_FAILED == dRes)
	{
		cout << "��������" << endl;
	}
	else
	{
		cout << "����ʧ��!" << endl;
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