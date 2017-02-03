#ifndef MUTEXGUARD_H
#define MUTEXGUARD_H

#include "Mutex.h"
class CMutexGuard
{
public:
	CMutexGuard(CMutex& mtx);
	virtual ~CMutexGuard();
private:
	CMutex& m_mtx;
};

#endif