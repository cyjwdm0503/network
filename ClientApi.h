#ifndef CLIENTAPI_H
#define CLIENTAPI_H
#include "SelectReactor.h"
#include "Client.h"

#include "contentsession.h"
#include "applicationsession.h"

class CClient;
class CChannel;

const size_t  MAXLENGTH = 1024;

class CClientApi:public CSelectReactor,public CHandler
{
public:
	CClientApi(const char* client,const char* server);
	virtual ~CClientApi();
	CClientApi();

	//被调度的过程
	virtual void SyncRun();

	virtual bool ExitInstance();

	virtual bool InitInstance();

	//获取对应的文件套接字
	virtual void GetIds( int* readid,int* writeid );

	//id准备好后，输入的过程
	virtual void HandleInput();

	//id准备好后，输出的过程
	virtual void HandleOutput();


private:
	CClient* m_client;
	CChannel* m_clientchannel;

	int m_leavewritelen;
	int m_leavereadlen;
	char* m_buf;
};




class CClientApplicationSession :public CApplicationSession
{
public:
	CClientApplicationSession(CDispatcher* dispatcher,CChannel* channel);
	int HandlePackage( CPackage* pPackage);
};

class ClientApp:public CSelectReactor
{
public:
	ClientApp(const char* client, const char* server);
	virtual bool InitInstance();
	CApplicationSession* m_Session;
	CClient* m_client;
	CChannel* m_clientchannel;
};
#endif
