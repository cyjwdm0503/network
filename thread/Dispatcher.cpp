#include "Dispatcher.h"
#include "Mutex.h"
#include "TimerHeap.h"
#include <iostream>

#ifdef WIN
#include <sys/timeb.h>
#include <sys/types.h>
#else
#include <sys/time.h>
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
	m_mtx.Lock();
	//单线程的同步event
	if(IsCurrentThread())
	{
		m_mtx.UnLock();
		if(handler != NULL)
			return handler->HandleEvent(event,dwParam,pParam);
		else
			return HandleEvent(event,dwParam,pParam);
	}

	//以下为多线程时的同步event
	//传入
	EventType *ev = m_EventQueue->AddSyncEvent(handler,event,dwParam,pParam);
	m_mtx.UnLock();
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
#ifdef WIN
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
	m_IOlist.push_back(handler);

}

void CDispatcher::RemoveHandler( CHandler* handler )
{
	//不能直接在内部用set的erase。不会正确删除
	CMutexGuard guard(m_mtx);
	for (ChandlerList::iterator i = m_IOlist.begin(); i != m_IOlist.end(); i++)
	{
		if ((*i) == handler) 
		{
			(*i) = NULL;
		}
	}
}

time_t CDispatcher::Time()
{
	return m_Time;
}



#ifdef EVENTDEBUG

class CTestReactor:public CDispatcher
{
public:

	virtual int HandleEvent( int nEventID, DWORD dwParam, void *pParam ) 
	{
		cout<<__FILE__<<"\t"<<__LINE__<<"\t"<<__FUNCTION__;
		cout<<GetCurrentThreadId()<<"\t"<<nEventID<<"\t"<<dwParam<<"\t"<<pParam<<endl;

		if(nEventID == EVENT_STOP)
			IsRun = false;

		return 0;
	}

	virtual void SyncRun() 
	{
		SleepMs(1000);
		std::set<CHandler*>::iterator it= m_IOlist.begin();
		for(; it!= m_IOlist.end(); it++)
		{
			if(*it != NULL)
			{
				(*it)->HandleInput();
				(*it)->HandleOupt();
			}
		}
	}

	virtual bool ExitInstance() 
	{
		cout<<__FILE__<<"\t"<<__LINE__<<"\t"<<__FUNCTION__<<endl;
		return true;
		//throw std::exception("The method or operation is not implemented.");
	}

	virtual bool InitInstance() 
	{
		cout<<__FILE__<<"\t"<<__LINE__<<"\t"<<__FUNCTION__<<endl;
		m_times = 0;
		return true;
		//throw std::exception("The method or operation is not implemented.");
	}

private:
	int m_times;

};

class CTestHandler:public CHandler
{
public:

	CTestHandler(EVENT_MSG msg,CDispatcher* select,CDispatcher* selector):m_msg(msg),m_select(select),CHandler(selector)
	{
		SetTimer(EVENT_ERR_OUTTIME,5000);
	}

	virtual void HandleInput() 
	{
		//throw std::exception("The method or operation is not implemented.");
	}

	virtual void HandleOutput() 
	{
		cout<<__FILE__<<"\t"<<__LINE__<<"\t"<<__FUNCTION__;
		cout<<GetCurrentThreadId()<<"\t"<<m_msg<<"\t"<<(void*)this<<endl;
		m_select->SendEvent(this,m_msg,GetCurrentThreadId(),(void*)this);

	}

	virtual void OnTimer( int event ) 
	{
		cout<<__FILE__<<"\t"<<__LINE__<<"\t"<<__FUNCTION__;
		cout<<(void*)this<<"\t"<<event<<endl;
		KillTimer(event);
	}

	virtual int HandleEvent( int event,DWORD dwParam,void* pParam ) 
	{
		
		cout<<__FILE__<<"\t"<<__LINE__<<"\t"<<__FUNCTION__;
		cout<<GetCurrentThreadId()<<"\t"<<event<<"\t"<<(void*)this<<endl;
		return 0;
	}
private:
	EVENT_MSG m_msg;
	CDispatcher* m_select;
};

int main(int ,char**)
{
	CTestReactor reactor;
	CTestReactor rect;
	//CTestHandler connecthandler(EVENT_RET_CONNECT,&reactor,&reactor);
	CTestHandler accepthandler(EVENT_RET_ACCEPT,&reactor,&reactor);
	rect.Create();
	reactor.Create();
	reactor.Join();
	rect.Join();
	return 0;
}
#endif
