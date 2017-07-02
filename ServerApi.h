/************************************************************************/
/* 利用Server.h提供的接口完成一个调度的接口。
*/
/************************************************************************/
#ifndef SERVERAPI_H
#define SERVERAPI_H
#include "SelectReactor.h"
#include "Handler.h"
#include "Server.h"
#include "SessionBase.h"
 
class CServer;
class CChannel;

const size_t  MAXLENGTH = 1024;

class CServerApi:public CHandler
{
public:
	CServerApi(CServer* server,CChannel* channel,CDispatcher* reactor);
	virtual ~CServerApi();
	CServerApi(CDispatcher* reactor);
	virtual void GetIds( int* readid,int* writeid );

	virtual void HandleInput();

	virtual void HandleOupt();
private:
	CServer* m_server;
	CChannel* m_serverchannel;

	int m_leavewritelen;
	int m_leavereadlen;
	char* m_buf;
};

class CServerSession :public CServerAcceptManager
{
public:
	CServerSession(CSelectReactor* selecter,const char* location );
	~CServerSession();
	virtual CSession* CreateSession(CChannel* channel);
private:

};


#endif

 