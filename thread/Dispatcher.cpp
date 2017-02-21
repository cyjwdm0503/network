#include "Dispatcher.h"
#include "Mutex.h"
#ifdef WIN32
#include <sys/timeb.h>
#include <sys/types.h>
#else
#endif
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
#ifdef WIN32
	struct _timeb timebuf;
	_ftime(&timebuf);
	m_Time = timebuf.time;
	m_MiscroTime = timebuf.millitm;
	m_clock = m_Time*1000+m_MiscroTime;
#else
	struct timeval timebuf;
	gettimeofday(&timebuf,0);
	m_Time = timebuf.tv_sec;
	m_MiscroTime = timebuf.tv_usec/1000;
	m_clock = m_Time*1000+m_MiscroTime;
	
#endif
}

void CDispatcher::SyncRun()
{

}


void CDispatcher::AddHandler( CHandler* handler )
{
	CMutexGuard guard(m_mtx);
	m_IOlist.insert(handler);

}

void CDispatcher::RemoveHandler( CHandler* handler )
{
	CMutexGuard guard(m_mtx);
	m_IOlist.erase(handler);
}
