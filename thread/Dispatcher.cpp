#include "Dispatcher.h"
#include "Mutex.h"
CDispatcher::CDispatcher()
{
	IsRun =  true;
}

CDispatcher::~CDispatcher()
{

}



void CDispatcher::RegisterTimer( CHandler* handler,int event,int ms )
{
	CMutexGuard guard(m_mtx);
}

void CDispatcher::RemoveTimer( CHandler* handler,int event )
{
	CMutexGuard guard(m_mtx);
}

bool CDispatcher::PostEvent( CHandler* handler,int event,DWORD dwParam,void* pParam )
{
	CMutexGuard guard(m_mtx);
	return true;
}

bool CDispatcher::SendEvent( CHandler* handler,int event,DWORD dwParam,void* pParam )
{
	CMutexGuard guard(m_mtx);
	return true;
}

void CDispatcher::DispatherTimer()
{
	CMutexGuard guard(m_mtx);
}

void CDispatcher::DispatherEvent()
{
	CMutexGuard guard(m_mtx);
}

void CDispatcher::Run()
{
	while(IsRun)
	{//
		SyncRun();
		SyncTimer();
		DispatherTimer();
		DispatherEvent();
	}
}

void CDispatcher::SyncTimer()
{
	 
}

void CDispatcher::SyncRun()
{
	 
}

