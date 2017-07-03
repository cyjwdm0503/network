#ifndef SESSIONBASE_H
#define SESSIONBASE_H


#include "Channel.h"
#include "SelectReactor.h"
#include "Handler.h"
#include "Channel.h"
#include "Server.h"

class CSession;
class CServerAcceptManager:public CSelectReactor, public CHandler
{
	
public:
	CServerAcceptManager(CSelectReactor* selecter,const char* location );
	virtual ~CServerAcceptManager();

	virtual void GetIds( int* readid,int* writeid );

	virtual void HandleInput();

	virtual void HandleOutput();

	virtual int HandleEvent( int event,DWORD dwParam,void* pParam );

	virtual void SyncRun();

	virtual CSession* CreateSession(CChannel* channel)= 0;

protected:
	CServer* m_server;
	CChannel* m_channel;
	//用于调度session的reactor
	CSelectReactor* m_serverreactor;
};

#endif