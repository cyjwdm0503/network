#ifndef  TIMERHEAP_H
#define  TIMERHEAP_H
#include "TimerQueue.h"
#include <queue>
#include <map>
using namespace  std;

class CTimerHeapNode
{
public:
	CHandler* handler;
	int event;
	DWORD elapse;
	DWORD expire;
};

class CNodeCom
{
public:
	bool operator ()(const CTimerHeapNode& node1, const CTimerHeapNode& node2)
	{
		return node1.expire < node1.expire;
	}
};
/*
bool NodeCom(const CTimerHeapNode &node1, const  CTimerHeapNode& node2) 
{
	if(node1.expire < node2.expire)
		return true;
	else
		return false;
}
typedef bool (*Com)(const CTimerHeapNode& node1, const CTimerHeapNode& node2);
class CTimerHeap:public CTimerQueue,public priority_queue<CTimerHeapNode,vector<CTimerHeapNode>,Com>
这里只能传入一个函数指针类型，在使用时才能传入一个具体的函数指针。
但是只能通过重载构造函数，传入对应的函数指针
因此一个好的方法是传入函数对象
*/
class CTimerHeap:public CTimerQueue,public priority_queue<CTimerHeapNode,vector<CTimerHeapNode>,CNodeCom>
{
public:

	virtual void RegisterTimer( CHandler* handler,DWORD event,DWORD elapse );

	virtual void RemoverTime( CHandler* handler,DWORD event );

	virtual void Expire( DWORD curmsclock );
	
	//
	//根据现在的时间同步
	virtual void SyncTime(DWORD curmsclock);
	virtual ~CTimerHeap();
	CTimerHeap(DWORD curmsclock);
private:
	DWORD m_beginclock;
	DWORD m_curclock;
};
#endif