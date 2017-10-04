#include "EventQueue.h"
#include <cstring>

CEventQueue::CEventQueue( int size )
{
	m_pPostEvent =  new EventType[size];
	memset(m_pPostEvent,0,size*sizeof(EventType));
	m_eventSize = size;
	m_readpos = 0;
	m_writepos = 0;
	pFirstSyncEventType =  NULL;
	pLastSyncEventType =  NULL;
}

CEventQueue::~CEventQueue()
{
	if(m_pPostEvent != NULL)
		delete [] m_pPostEvent;
	m_pPostEvent =  NULL;
}

//异步的event
bool CEventQueue::AddPostEvent( CHandler* handler,EVENT_MSG nEventID, DWORD dwParam, void *pParam )
{
	m_mtx.Lock();
	//预留一个空位
	if( (m_writepos+1)%m_eventSize == m_readpos)
	{
		m_mtx.UnLock();
		return false;
	}
	EventType* event =  m_pPostEvent+m_writepos;
	event->handler = handler;
	event->dwParam = dwParam;
	event->pParam = pParam;
	//event->pThisAddr = handler;
	event->event_msg = nEventID;
	event->retValue = 0;
	//设置为空是用来确定是Send还是Post
	event->pThisAddr =  NULL;
	m_writepos++;
	if(m_writepos >= m_eventSize )
	{
		m_writepos = 0;
	}

	m_mtx.UnLock();
	return true;
}

//同步的event
EventType* CEventQueue::AddSyncEvent( CHandler* handler,EVENT_MSG nEventID, DWORD dwParam, void *pParam )
{
	m_mtx.Lock();

	EventType* event = new EventType;
	event->handler = handler;
	event->dwParam = dwParam;
	event->pParam = pParam;
	//event->pThisAddr = handler;
	event->event_msg = nEventID;
	event->retValue = 0;
	event->sem.Lock();

	SyncEventType* syncevent = new SyncEventType;
	syncevent->event =  event;
	syncevent->pNext =  NULL;
	event->pThisAddr = syncevent;

	if(pFirstSyncEventType == NULL)
	{
		pLastSyncEventType =  pFirstSyncEventType = syncevent;
	}
	else
	{
		pLastSyncEventType->pNext = syncevent;
		pLastSyncEventType =  syncevent;
	}

	m_mtx.UnLock();
	return syncevent->event;
}

//取出event
bool CEventQueue::PeekEvent( EventType& event )
{
	m_mtx.Lock();
	if(pFirstSyncEventType != NULL)
	{
		event = *(pFirstSyncEventType->event);
		pFirstSyncEventType = pLastSyncEventType->pNext;		
		m_mtx.UnLock();
		return true;
	}
	//预留一个空位
	if(m_readpos != m_writepos)
	{
		event = m_pPostEvent[m_readpos];
		event.pThisAddr =  NULL;
		m_readpos++;
		if(m_readpos >= m_eventSize)
			m_readpos = 0;
		m_mtx.UnLock();
		return true;
	}

	m_mtx.UnLock();
	return false;
}
