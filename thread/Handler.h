#ifndef HANDLER_H
#define HANDLER_H
//#include "Dispatcher.h"
typedef unsigned long       DWORD;
class CDispatcher;
class CHandler
{
public:
	CHandler(CDispatcher* selecter);
	virtual ~CHandler();
	virtual void GetIds(int* readid,int* writeid){};
	virtual void HandleInput(){};
	virtual void HandleOupt(){};
	virtual void OnTimer(int event){};
	virtual int HandleEvent(int event,DWORD dwParam,void* pParam);
	virtual bool PostEvent(int event, DWORD dwParam,void* pParam);
	virtual void SetTimer(int event,int elapse);
	virtual int SendEvent(int event, DWORD dwParam, void* pParam);
private:
	CDispatcher* m_dispatcher;
};


#endif