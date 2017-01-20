#ifndef DISPATCHER_H
#define DISPATCHER_H
#include "Thread.h"
#include "Handler.h"
#include <list>
#include "MutexGuard.h"

class CDispatcher:public CThread
{
public:
	CDispatcher();
	~CDispatcher();

	void RegisterTimer(CHandler* handler,int event,int ms);
	void RemoveTimer(CHandler* handler,int event);
	bool PostEvent(CHandler* handler,int event,DWORD dwParam,void* pParam);//“Ï≤Ω
	bool SendEvent(CHandler* handler,int event,DWORD dwParam,void* pParam);//Õ¨≤Ω
	void DispatherTimer();
	void DispatherEvent();
	virtual void Run();
	void SyncTimer();
	virtual void SyncRun();
protected:

	CMutex m_mtx;
	bool IsRun;
};
#endif