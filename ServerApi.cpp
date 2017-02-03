#include "ServerApi.h"

CServerApi::CServerApi(const char* server ):CSelectReactor(),CHandler(this)
{
	m_server =  new CServer();
	m_server->CreateServer(server);
	
}

CServerApi::CServerApi():CHandler(this)
{
	m_server = NULL;
	m_serverchannel = NULL;
}

CServerApi::~CServerApi()
{
	if (m_server != NULL)
	{
		delete m_server;
		m_server = NULL;
	}
}

void CServerApi::SyncRun()
{
	;
}

bool CServerApi::ExitInstance()
{
	return CSelectReactor::ExitInstance();
}

bool CServerApi::InitInstance()
{
	return CSelectReactor::InitInstance();
}

void CServerApi::GetIds( int* readid,int* writeid )
{
	;// m_serverchannel->Getfd(); = m_server->AcceptClient();
}

void CServerApi::HandleInput()
{

}

void CServerApi::HandleOupt()
{

}