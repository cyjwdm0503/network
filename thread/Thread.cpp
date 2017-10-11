#include "Thread.h"
#include <cstring>


CThread::CThread()
{
	m_IDThread = 0;
#ifdef WIN32
    m_hThread = (THREAD_HANDLE)0;
#else
    memset(&m_hThread,0,sizeof(m_hThread));
#endif

}

CThread::~CThread()
{
	m_IDThread = 0;
#ifdef WIN32
    m_hThread = (THREAD_HANDLE)0;
#else
	 memset(&m_hThread,0,sizeof(m_hThread));
#endif
}

bool CThread::Create( void )
{
#ifdef WIN32
    m_hThread = ::CreateThread(NULL,0,_ThreadEntry,this,0,&m_IDThread);
	if(m_hThread == NULL)
		return false;
#else
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int ret = pthread_create(&m_hThread,NULL,_ThreadEntry,(void*)this);
	if(ret != 0)
		return false;
#endif
	return true;
}

bool CThread::ExitInstance()
{
	return true;
}

bool CThread::InitInstance()
{
	return true;
}

void CThread::Run()
{

}

void CThread::SleepMs(int ms)
{
#ifdef WIN32
	::Sleep(ms);
#else
    usleep(ms*1000);
#endif
}

THREAD_HANDLE CThread::GetHandle()
{
	return m_hThread;
}

#ifdef WIN32
DWORD WINAPI CThread::_ThreadEntry( LPVOID pParam )
#else
void * CThread::_ThreadEntry(void *pParam)
#endif // WINDOWS
{
	CThread* pthread = (CThread*)pParam;
	if(pthread != NULL)
	{
		if(pthread->InitInstance() != false)
		{
			pthread->Run();
		}
		pthread->ExitInstance();
	}
	return 0;
}


bool CThread::Join()
{
#ifdef WIN32
	return (WaitForSingleObject(GetHandle(),INFINITE) != 0);
#else
    void* status;
    return pthread_join(m_hThread,&status);
#endif
}

bool CThread::IsCurrentThread()
{
#ifdef WIN32
	return ::GetCurrentThreadId() == m_IDThread;
#else
	return pthread_self() == m_hThread;
#endif
}
