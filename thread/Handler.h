#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H
//#include "Dispatcher.h"
typedef unsigned long       DWORD;
class CDispatcher;
class CHandler
{
public:
	CHandler(CDispatcher* selecter);
	virtual ~CHandler();
	virtual void GetIds(int* readid,int* writeid);;
	virtual void HandleInput();;
	virtual void HandleOutput();;
	virtual void OnTimer(int event);;
	virtual int HandleEvent(int event,DWORD dwParam,void* pParam);
	bool PostEvent(int event, DWORD dwParam,void* pParam);
	void SetTimer(int event,int elapse);
	void KillTimer(int event);
	int SendEvent(int event, DWORD dwParam, void* pParam);
protected:
	CDispatcher* m_dispatcher;
};


#endif