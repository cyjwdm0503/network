/**
�ṩ����event��ȡ��event������
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
	void* pThisAddr;//���ڻش�
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
	//��Ϊ����Ҫ���ⲿ���ݽ��ֵ����˴��ⲿ����eventtype�����߷���eventtype
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