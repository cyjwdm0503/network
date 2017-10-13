#include "Mutex.h"


CMutex::CMutex()
{
#ifdef WIN
	m_lock =  CreateMutex(NULL,FALSE,NULL);
#else
    pthread_mutex_init(&m_lock,NULL);
#endif
}

CMutex::CMutex( const char* name )
{
#ifdef WIN
	m_lock =  CreateMutex(NULL,FALSE,name);
	if(m_lock != NULL)
	{
		if(GetLastError() == ERROR_ALREADY_EXISTS)
		{
			m_lock =  OpenMutex(MUTEX_ALL_ACCESS,FALSE,name);
		}
	}
#else
    pthread_mutex_init(&m_lock,NULL);
#endif
}

CMutex::~CMutex()
{
#ifdef WIN
	CloseHandle(m_lock);
#else
    pthread_mutex_destroy(&m_lock);
#endif
}

void CMutex::Lock()
{
#ifdef WIN
	WaitForSingleObject(m_lock,INFINITE);
#else
    pthread_mutex_lock(&m_lock);
#endif

}

void CMutex::UnLock()
{
#ifdef WIN
	ReleaseMutex(m_lock);
#else
    pthread_mutex_unlock(&m_lock);
#endif
}

bool CMutex::TryLock()
{
#ifdef WIN
	return (WaitForSingleObject(m_lock,0) == WAIT_OBJECT_0);
#else
    return  pthread_mutex_trylock(&m_lock) == 0;
#endif
}

