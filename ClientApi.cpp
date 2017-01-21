#include "ClientApi.h"
#include <iostream>
#include "Client.h"
using namespace  std;


void CClientApi::SyncRun()
{
	CSelectReactor::SyncRun();
}


bool CClientApi::ExitInstance()
{
	std::cout<<"CClientApi::ExitInstance()"<<std::endl;
	return true;
}

bool CClientApi::InitInstance()
{
	return true;
}

void CClientApi::GetIds( int* readid,int* writeid )
{
	if(m_clientchannel == NULL)
	{
		(*readid) = 0;
		(*writeid) = 0;
		return;
	}
	int fd = m_clientchannel->Getfd();
	if(m_leavewritelen > 0)
	{
		(*writeid) =  fd;
	}
	else
	{
		(*writeid) = 0;
	}

	(*readid) =fd;

}

void CClientApi::HandleInput()
{ 
	if(m_clientchannel != NULL)
	{
		int len = m_clientchannel->Read(MAXLENGTH,m_buf);
		if(len > 0)
			m_buf[len] = '\0';
		m_leavewritelen = len;
		cout<<"CClientApi::HandleInput:"<<len<<" char content:"<<m_buf<<endl;
	}
}

void CClientApi::HandleOupt()
{
	if(m_clientchannel != NULL)
	{
		int len = m_clientchannel->Write(MAXLENGTH,m_buf);
		m_leavewritelen = 0;
		cout<<"CClientApi::HandleOupt:"<<len<<" char content:"<<m_buf<<endl;
	}
}

CClientApi::CClientApi( const char* clientip,const char* serverip ):CHandler(this),m_clientchannel(NULL)
{
	AddHandler(this);
	m_buf = new char[MAXLENGTH+1];
	strcpy(m_buf,"12345678");
	m_leavereadlen = 0;
	m_leavewritelen = 1;
	m_client = new CClient();
	m_client->CreateClient(clientip);

	m_clientchannel = m_client->ConnectServer(serverip);
}

CClientApi::CClientApi():CSelectReactor(),CHandler(this)
{
	;
}

CClientApi::~CClientApi()
{

}

