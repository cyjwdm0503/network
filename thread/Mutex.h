#ifndef MUTEX_H
#define MUTEX_H

#include "Common.h"

class CMutex
{
public:
	CMutex();
	CMutex(const char* name);
	virtual ~CMutex();
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
