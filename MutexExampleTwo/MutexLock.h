#pragma once
#ifndef __MY_MUTEX_H
#define __MY_MUTEX_H
#include <windows.h>

class CMyMutex
{
public:
	CMyMutex();

	virtual ~CMyMutex();

	void Lock();

	void UnLock();

private:
	HANDLE m_hMutex;
};

class CMutexLock
{
public:
	CMutexLock(CMyMutex* pMutex);

	virtual ~CMutexLock();

private:
	CMyMutex*           m_pMutex;
};

#endif;
