/**
提供放入event和取出event的序列
*/
#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "Thread.h"
#include "Common.h"
#include "Handler.h"
#include "Semaphore.h"
#include "Mutex.h"

struct EventType
{
	CHandler* handler;
	EVENT_MSG event_msg;
	DWORD dwParam;
	void* pParam;
	int retValue;
	CSemaphore sem;
	void* pThisAddr;//用于回传
	void* pNext;
};
struct SyncEventType
{
	EventType* event;
	SyncEventType* pNext;
};
class CEventQueue
{
public:
	CEventQueue(int size);
	virtual ~CEventQueue();
	bool AddPostEvent(CHandler* handler,EVENT_MSG nEventID, DWORD dwParam, void *pParam);
	//因为这里要向外部传递结果值。因此从外部传入eventtype。或者返回eventtype
	EventType* AddSyncEvent(CHandler* handler,EVENT_MSG nEventID, DWORD dwParam, void *pParam);
	bool PeekEvent(EventType& event);
protected:
	EventType* m_pPostEvent;
	int  m_eventSize;
	int m_readpos;
	int m_writepos;

	SyncEventType* pFirstSyncEventType;
	SyncEventType* pLastSyncEventType;

	CMutex m_mtx;
};

#endif