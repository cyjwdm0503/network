#include "Dispatcher.h"
#include "Mutex.h"
#include "TimerHeap.h"

#ifdef WIN32
#include <sys/timeb.h>
#include <sys/types.h>
#else
#endif
CDispatcher::CDispatcher()
{
	SyncTimer();
	IsRun =  true;
	m_Timerheap =  new CTimerHeap(m_clock);
	m_EventQueue = new CEventQueue(10);
}

CDispatcher::~CDispatcher()
{
	if(m_Timerheap != NULL)
		delete m_Timerheap;
	m_Timerheap =  NULL;
}



void CDispatcher::RegisterTimer( CHandler* handler,int event,int ms )
{
	//CMutexGuard guard(m_mtx);
	m_Timerheap->RemoverTime(handler,event);
	m_Timerheap->RegisterTimer(handler,event,ms);	
}

void CDispatcher::RemoveTimer( CHandler* handler,int event )
{
	//CMutexGuard guard(m_mtx);
	m_Timerheap->RemoverTime(handler,event);
}

bool CDispatcher::PostEvent( CHandler* handler,EVENT_MSG event,DWORD dwParam,void* pParam )
{
	m_EventQueue->AddPostEvent(handler,event,dwParam,pParam);
	return true;
}

int CDispatcher::SendEvent( CHandler* handler,EVENT_MSG event,DWORD dwParam,void* pParam )
{
	//单线程的同步event
	if(IsCurrentThread())
	{
		if(handler != NULL)
			return handler->HandleEvent(event,dwParam,pParam);
		else
			return HandleEvent(event,dwParam,pParam);
	}

	//以下为多线程时的同步event
	//传入
	EventType *ev = m_EventQueue->AddSyncEvent(handler,event,dwParam,pParam);
	
	//等待解锁
	ev->sem.Lock();
	return ev->retValue;
}

void CDispatcher::DispatherTimer()
{
	//CMutexGuard guard(m_mtx);
	m_Timerheap->Expire(m_clock);
}

void CDispatcher::DispatherEvent()
{
	CMutexGuard guard(m_mtx);
	EventType event;
	while (m_EventQueue->PeekEvent(event) && IsRun)
	{
		int ret = 0;
		if(event.handler != NULL)
		{
			ret = event.handler->HandleEvent(event.event_msg,event.dwParam,event.pParam);
		}
		else
		{
			ret = HandleEvent(event.event_msg,event.dwParam,event.pParam);
		}
		if(event.pThisAddr != NULL)
		{
			event.retValue = ret;
			event.sem.UnLock();
		}

	}
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
