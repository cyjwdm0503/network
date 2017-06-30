#include "SessionBase.h"
#include <iostream>
#include "ServerApi.h"

void CServerAcceptManager::GetIds( int* readid,int* writeid )
{
	if(m_channel != NULL)
		*readid = m_channel->Getfd();
	*writeid = 0;
}

void CServerAcceptManager::HandleInput()
{
	//�ڲ�����channel��ʽ�д����飬��Ϊ�漰��serverapi���̶߳�ȡchannel
	CChannel* channel = m_server->AcceptClient();
	if(channel != NULL)
	{
		cout<<"void CSessionBase::HandleInput() success:"<<channel->Getfd()<<endl;
		//CServerApi* serverapi= new CServerApi(m_server,channel,m_serverreactor);
		CreateSession(channel);
		if(channel->GetService()->GetNChannel() == SOCK_DGRAM)
		{//���Ҳ��ڽ������ҵ���
			this->RemoveHandler(this);
		}
	}
}

void CServerAcceptManager::HandleOupt()
{
	;
}

int CServerAcceptManager::HandleEvent( int event,DWORD dwParam,void* pParam )
{
	return 0;
}

CServerAcceptManager::~CServerAcceptManager()
{
	if(m_channel != NULL)
		delete m_channel;
	m_channel = NULL;
	if(m_server != NULL)
		delete  m_server;
	m_server = NULL;
	m_serverreactor =  NULL;
}

CServerAcceptManager::CServerAcceptManager( CSelectReactor* selecter,const char* location ):CHandler(this)
{
	AddHandler(this);
	m_server = new CServer();
	m_channel = m_server->CreateServer(location);
	m_serverreactor =  selecter;
}

void CServerAcceptManager::SyncRun()
{
	if(m_channel->GetService()->GetNChannel() == SOCK_STREAM)
		CSelectReactor::SyncRun();
	else
	{
		ChandlerList::iterator it= m_IOlist.begin();
		for(; it!= m_IOlist.end(); it++)
		{
			if((*it) != NULL)
				(*it)->HandleInput();
		}
	}
}
