#ifndef DISPATCHER_H
#define DISPATCHER_H
#include "Thread.h"
#include "Handler.h"
#include <list>
#include <set>
#include "MutexGuard.h"
#include "TimerQueue.h"

class CDispatcher:public CThread
{
public:
	CDispatcher();
	virtual ~CDispatcher();

	void RegisterTimer(CHandler* handler,int event,int ms);
	void RemoveTimer(CHandler* handler,int event);
	//异步event
	bool PostEvent(CHandler* handler,int event,DWORD dwParam,void* pParam);//异步
	//同步event
	bool SendEvent(CHandler* handler,int event,DWORD dwParam,void* pParam);//同步
	void DispatherTimer();
	void DispatherEvent();
	virtual void Run();
	void SyncTimer();
	virtual void SyncRun();
	void  AddHandler( CHandler* handler );
	void  RemoveHandler( CHandler* handler );
protected:
	std::set<CHandler*> m_IOlist;

	CTimerQueue* m_Timerheap;
	CMutex m_mtx;
	bool IsRun;

	DWORD m_MiscroTime;
	DWORD m_Time;
	DWORD m_clock;
};
#endif