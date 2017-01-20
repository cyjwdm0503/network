#ifndef MUTEX_H
#define MUTEX_H

#include "Common.h"

#ifdef WIN32
#include <windows.h>
#else
#include "pthread.h"
#endif

class CMutex
{
public:
	CMutex();
	CMutex(const char* name);
	~CMutex();
	void Lock();
	void UnLock();
	bool TryLock();

public:
#ifdef WIN32
	HANDLE m_lock;
#else
    pthread_mutex_t m_lock;
#endif
};

#endif
