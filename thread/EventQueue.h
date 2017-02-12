/**
提供放入event和取出event的序列
*/
#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "Thread.h"
#include "Common.h"
#include "Handler.h"
#include "Semaphore.h"

struct EventType
{
	CHandler* handler;
	EVENT_MSG event_msg;
	DWORD dwParam;
	void* pParam;
	int retValue;
	CSemaphore sem;
	void* pThisAddr;//用于回传
};

class CEventQueue
{
	CEventQueue();
	virtual ~CEventQueue();
	bool AddPostEvent(CHandler* handler,EVENT_MSG nEventID, DWORD dwParam, void *pParam);
	bool AddSyncEvent(CHandler* handler,EVENT_MSG nEventID, DWORD dwParam, void *pParam);
	bool PeekEvent(EventType& event);
};

#endif