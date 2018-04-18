#pragma once
#ifndef _MY_EVENT_H
#define _MY_EVENT_H

#include <windows.h>

class CMyEvent
{
public:
	CMyEvent()
	{
		m_hEvent = CreateEvent(NULL     /*安全属性指针*/
			, false                     /*复位方式*/
			, true                      /*初始化状态*/
			, NULL                      /*事件名称*/
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