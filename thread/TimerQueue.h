#ifndef TIMERQUEUE_H
#define TIMERQUEUE_H

#include "Handler.h"

/************************************************************************/
/* �����ṩ�Ķ�ʱ������ӿ�*/
/************************************************************************/
class  CTimerQueue
{
public:
	virtual void RegisterTimer(CHandler* handler,DWORD event,DWORD elapse ) =0;
	
	virtual void RemoverTime(CHandler* handler,DWORD event) =0 ;

	virtual void Expire(DWORD curclock) = 0;
	virtual ~CTimerQueue(){};
	CTimerQueue(){};
};

#endif
