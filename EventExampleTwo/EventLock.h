#pragma once
#ifndef _MY_EVENT_H
#define _MY_EVENT_H

#include <windows.h>

class CMyEvent
{
public:
	CMyEvent()
	{
		m_hEvent = CreateEvent(NULL     /*��ȫ����ָ��*/
			, false                     /*��λ��ʽ*/
			, true                      /*��ʼ��״̬*/
			, NULL                      /*�¼�����*/
		);

		if (NULL == m_hEvent)
		{
			return;
		}
	}

	~CMyEvent()
	{
		CloseHandle(m_hEvent);
	}

public:
	void Lock()
	{
		WaitForSingleObject(m_hEvent, INFINITE);
	}

	void UnLock()
	{
		SetEvent(m_hEvent);
	}

private:
	HANDLE                  m_hEvent;
};

class CEventAutoLock
{
public:
	CEventAutoLock(CMyEvent* pMyEvent)
		: m_pMyEvent(pMyEvent)
	{
		if (NULL != m_pMyEvent)
		{
			m_pMyEvent->Lock();
		}
	}

	~CEventAutoLock()
	{
		m_pMyEvent->UnLock();
	}

private:
	CMyEvent                *m_pMyEvent;
};

#endif