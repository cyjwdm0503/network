#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "Common.h"
class CSemaphore
{
public:
	CSemaphore(int count, const char* name = NULL);
	void Lock(void);
	void UnLock();
	bool TryLock();
private:
	HANDLE m_semap;
};
#endif