#include "Semaphore.h"
CSemaphore::CSemaphore( int count,const char* name)
{
#ifdef WIN32
	m_semap = CreateSemaphore(NULL,count,count,name);
	if(m_semap != NULL)
	{
		if(GetLastError() == ERROR_ALREADY_EXISTS)
		{
			m_semap = OpenSemaphore(SEMAPHORE_ALL_ACCESS,FALSE,name);
		}
	}
#else
	m_count = count;
	pthread_mutex_init(&mtx,NULL);
	pthread_cond_init(&m_semap,NULL);
#endif
}

CSemaphore::~CSemaphore()
{
#ifdef WIN32
	CloseHandle(m_semap);
#else

	pthread_cond_destroy(&m_semap);
	pthread_mutex_destroy(&mtx);
#endif
}

void CSemaphore::Lock( int* pCount )
{
#ifdef WIN32
	WaitForSingleObject(m_semap,INFINITE);
#else
	pthread_mutex_lock(&mtx);
	while(m_count <=0 )
	{
		pthread_cond_wait(&m_semap,&mtx);
	}
	if(m_count >0)
	{
		m_count--;
		if(pCount != NULL)
		{
			*pCount = m_count;
		}
	}
	pthread_mutex_unlock(&mtx);
#endif // WINDOWS
}

void CSemaphore::UnLock(int* pCount)
{
#ifdef WIN32
	ReleaseSemaphore(m_semap,1,NULL);
#else
	pthread_mutex_lock(&mtx);
	m_count++;
	if(pCount != NULL)
	{
		*pCount = m_count;
	}
	pthread_cond_signal(&m_semap);
	pthread_mutex_unlock(&mtx);
#endif // WINDOWS

}

bool CSemaphore::TryLock(int* pCount)
{
#ifdef WIN32
	return WaitForSingleObject(m_semap,0) == WAIT_OBJECT_0 ;
#else
	pthread_mutex_lock(&mtx);
	struct timespec t;
	t.tv_sec = time(NULL);
	t.tv_nsec = 0;
	if(m_count <=0)
		if(pthread_cond_timedwait(&m_semap,&mtx,&t) !=0 )
		{
			pthread_mutex_unlock(&mtx);
			return false;
		}
		m_count--;
		if(pCount!= NULL)
		{
			*pCount = m_count;
		}
		pthread_mutex_unlock(&mtx);
		return true;
#endif
}

