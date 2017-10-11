#include "MutexGuard.h"

CMutexGuard::CMutexGuard( CMutex& mtx ):m_mtx(mtx)
{
	m_mtx.Lock();
}

CMutexGuard::~CMutexGuard()
{
	m_mtx.UnLock();
}
