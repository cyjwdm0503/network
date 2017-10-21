#ifndef THREAD_TIMERQUEUE_H
#define THREAD_TIMERQUEUE_H

#include "Handler.h"
#include <ctime>
/************************************************************************/
/* 对外提供的定时器抽象接口*/
/************************************************************************/
class  CTimerQueue
{
public:
	virtual void RegisterTimer(CHandler* handler,DWORD event,DWORD elapse ) =0;
	
	virtual void RemoverTime(CHandler* handler,DWORD event) =0 ;

	virtual void Expire(time_t curclock) = 0;
	virtual ~CTimerQueue(){};
	CTimerQueue(){};
};

#endif
