#ifndef THREAD_SEMAPHORE_H
#define THREAD_SEMAPHORE_H

#include "Common.h"
class CSemaphore
{
public:
	//1退化为mutex?
	CSemaphore(int count = 1, const char* name = NULL);
	virtual ~CSemaphore();
	void Lock(int* pCount= NULL);
	void UnLock(int* pCount= NULL);
	bool TryLock(int* pCount=NULL);
private:
    #ifdef WIN
        HANDLE m_semap;
	#else
         pthread_cond_t  m_semap;
         pthread_mutex_t  mtx;
         int m_count;
	#endif
};
#endif