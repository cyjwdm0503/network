#ifndef CLIENTAPI_H
#define CLIENTAPI_H
#include "SelectReactor.h"
#include "Client.h"

#include "contentsession.h";

class CClient;
class CChannel;

const size_t  MAXLENGTH = 1024;

class CClientApi:public CSelectReactor,public CHandler
{
public:
	CClientApi(const char* client,const char* server);
	virtual ~CClientApi();
	CClientApi();

	//�����ȵĹ���
	virtual void SyncRun();

	virtual bool ExitInstance();

	virtual bool InitInstance();

	//��ȡ��Ӧ���ļ��׽���
	virtual void GetIds( int* readid,int* writeid );

	//id׼���ú�����Ĺ���
	virtual void HandleInput();

	//id׼���ú�����Ĺ���
	virtual void HandleOupt();


private:
	CClient* m_client;
	CChannel* m_clientchannel;

	int m_leavewritelen;
	int m_leavereadlen;
	char* m_buf;
};

class CClientSession:public CSelectReactor
{
public:
	CClientSession(const char* client,const char* server);
	virtual bool InitInstance();
	CContentSession* m_Session;
	CClient* m_client;
	CChannel* m_clientchannel;
};
#endif
