#include "TimerHeap.h"

const DWORD MAX_TIMER_HEAP_TIMEOUT = 3600*24*1000; 
//��ʱ����������

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
		if(c[index].handler == handler &&
			(c[index].event == event || event == 0))
		{//ɾ��ĳ��handler���Ӧ��event.���߶�Ӧhandler��Ӧ��ȫ��event
			c[index].handler = NULL;
		}
	}
}

void CTimerHeap::Expire( DWORD curclock )
{
	//�޸����ƫ��ʱ��
	SyncTime(curclock);

	while(size()>0)
	{
		CTimerHeapNode node = top();
		if(node.expire > m_curclock)
		{//���µ���Ӧ�ڵ��ʱ�����ڵ�ǰʱ��
			break;
		}
		
		//ȡ���Ľڵ�
		pop();
		if(node.handler != NULL)
		{
			node.expire = m_curclock + node.elapse;
			push(node);
			node.handler->OnTimer(node.event);
		}
		

	}
}

CTimerHeap::~CTimerHeap()
{

}

void CTimerHeap::SyncTime( DWORD curclock )
{
	m_curclock = curclock - m_beginclock;
}

CTimerHeap::CTimerHeap( DWORD curclock )
{
	m_beginclock = curclock;
}

