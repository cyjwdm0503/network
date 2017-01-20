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

#endif
}

void CSemaphore::Lock( void )
{
#ifdef WIN32
	WaitForSingleObject(m_semap,INFINITE);
#else

#endif // WINDOWS
}

void CSemaphore::UnLock()
{
#ifdef WIN32
	ReleaseSemaphore(m_semap,1,NULL);
#else

#endif // WINDOWS

}

bool CSemaphore::TryLock()
{
#ifdef WIN32
	return WaitForSingleObject(m_semap,0) == WAIT_OBJECT_0 ;
#else

#endif
}

