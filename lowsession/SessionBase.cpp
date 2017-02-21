#include "SessionBase.h"
#include <iostream>
#include "ServerApi.h"

void CSessionBase::GetIds( int* readid,int* writeid )
{
	if(m_channel != NULL)
		*readid = m_channel->Getfd();
	*writeid = 0;
}

void CSessionBase::HandleInput()
{
	//内部生成channel方式有待考验，因为涉及到serverapi多线程读取channel
	CChannel* channel = m_server->AcceptClient();
	if(channel != NULL)
	{
		cout<<"void CSessionBase::HandleInput() success:"<<channel->Getfd()<<endl;
		CServerApi* serverapi= new CServerApi(m_server,channel,m_serverreactor);
	}
}

void CSessionBase::HandleOupt()
{
	;
}

void CSessionBase::HandleEvent( int event,DWORD dwParam,void* pParam )
{
	;
}

CSessionBase::~CSessionBase()
{
	if(m_channel != NULL)
		delete m_channel;
	m_channel = NULL;
	if(m_server != NULL)
		delete  m_server;
	m_server = NULL;
	m_serverreactor =  NULL;
}

CSessionBase::CSessionBase( CSelectReactor* selecter,const char* location ):CHandler(this)
{
	m_server = new CServer();
	m_channel = m_server->CreateServer(location);
	m_serverreactor =  selecter;
}
