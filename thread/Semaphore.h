#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "Common.h"
class CSemaphore
{
public:
	CSemaphore(int count, const char* name = NULL);
	virtual ~CSemaphore();
	void Lock(int* pCount= NULL);
	void UnLock(int* pCount= NULL);
	bool TryLock(int* pCount=NULL);
private:
    #ifdef WIN32
        HANDLE m_semap;
	#else
         pthread_cond_t  m_semap;
         pthread_mutex_t  mtx;
         int m_count;
	#endif
};
#endif