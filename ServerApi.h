/************************************************************************/
/* 利用Server.h提供的接口完成一个调度的接口。
*/
/************************************************************************/
#ifndef SERVERAPI_H
#define SERVERAPI_H
#include "SelectReactor.h"
#include "Handler.h"
#include "Server.h"
 
class CServer;
class CChannel;

const size_t  MAXLENGTH = 1024;

class CServerApi:public CSelectReactor,public CHandler
{
public:
	CServerApi(const char* server);
	virtual ~CServerApi();
	CServerApi();
	virtual void SyncRun();

	virtual bool ExitInstance();

	virtual bool InitInstance();

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



#endif

 