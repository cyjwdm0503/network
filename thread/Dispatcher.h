#ifndef DISPATCHER_H
#define DISPATCHER_H
#include "Thread.h"
#include "Handler.h"
#include <list>
#include <set>
#include "MutexGuard.h"
#include "TimerQueue.h"
#include "EventQueue.h"
#include "TimerHeap.h"

class CDispatcher:public CThread
{
public:
	CDispatcher();
	virtual ~CDispatcher();

	void RegisterTimer(CHandler* handler,int event,int ms);
	void RemoveTimer(CHandler* handler,int event);
	//异步event
	bool PostEvent(CHandler* handler,EVENT_MSG event,DWORD dwParam,void* pParam);//异步
	//同步event
	int SendEvent(CHandler* handler,EVENT_MSG event,DWORD dwParam,void* pParam);//同步

	virtual int HandleEvent(int nEventID, DWORD dwParam, void *pParam){return 0;};
	
	void DispatherTimer();
	void DispatherEvent();
	void Run();
	void SyncTimer();
	virtual void SyncRun();
	void  AddHandler( CHandler* handler );
	void  RemoveHandler( CHandler* handler );
protected:
	typedef std::list<CHandler*> ChandlerList;
	ChandlerList m_IOlist;

	CTimerQueue* m_Timerheap;
	CEventQueue* m_EventQueue;
	CMutex m_mtx;
	bool IsRun;

	DWORD m_MiscroTime;
	DWORD m_Time;
	DWORD m_clock;
};
#endif
