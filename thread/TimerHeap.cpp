#include "TimerHeap.h"

void CTimerHeap::RegisterTimer( CHandler* handler,DWORD event,DWORD elapse )
{
	CTimerHeapNode node;
	node.handler = handler;
	node.event = event;
	node.elapse =elapse;
	node.expire = elapse;

	push(node);
}

void CTimerHeap::RemoverTime( CHandler* handler,DWORD event )
{
	for(int index=0; index <size(); index++)
	{

	}
}

void CTimerHeap::Expire( DWORD curclock )
{

}

CTimerHeap::~CTimerHeap()
{

}

