#include "ServerApi.h"
#include "channelpackage.h"
#include <iostream>

static int SERVERVERSION = 100;
CServerApi::CServerApi(CServer* server,CChannel* channel,CDispatcher* reactor):CHandler(reactor)
{
	//AddHandler(this);
	//m_server =  new CServer();
	//m_server->CreateServer(server);
	////实际为client与server通信的chanel
	//m_serverchannel = m_server->AcceptClient();
	m_server = server;
	m_serverchannel = channel;
	m_leavewritelen = 0;

}

CServerApi::CServerApi(CDispatcher* reactor):CHandler(reactor)
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


void CServerApi::GetIds( int* readid,int* writeid )
{
	if(m_serverchannel == NULL)
	{
		(*readid) = 0;
		(*writeid) = 0;
		return;
	}
	if(!m_serverchannel->Available())
	{
		(*readid) = 0;
		(*writeid) = 0;
		return;
	}
	int fd = m_serverchannel->Getfd();
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

void CServerApi::HandleInput()
{
	CChannelPackage package(CHANNELPACKAGE_ID,1024);
	if(m_serverchannel != NULL)
	{
		int re = package.ReadFromChannel(m_serverchannel);
		if(re > 0)
		{
			m_leavewritelen = re;
			cout<<"package:len"<<package.GetPackageLen();
		}
		else
		{//channel在断线后应该通知server.重新进入accept流程。
			m_serverchannel->Disconnect();
			return ;
		}
		CPackage pack(PACKAGE_ID);
		if(package.PopPackage(&pack))
		{
			pack.MakePackage();
			cout<<"CServerApi::HandleInput:"<<re<<"fp"<<m_serverchannel->Getfd()<<" char content:"<<"\t"<<pack.GetHeader()->VERSION<<endl;
		}
	}
}

void CServerApi::HandleOupt()
{
	CChannelPackage package(CHANNELPACKAGE_ID,MAXLENGTH);
	CPackage pack(PACKAGE_ID,MAXLENGTH);
	pack.GetHeader()->VERSION = ++SERVERVERSION;
	pack.PushHeader();
	package.PushPackage(&pack);
	if(m_serverchannel != NULL)
	{
		int len = m_serverchannel->Write(package.GetPackageLen(),package.GetPackagePtr());
		m_leavewritelen = 0;
		cout<<"package:len"<<package.GetPackageLen()<<"CServerApi::HandleOupt:"<<len<<"fp"<<m_serverchannel->Getfd()<<" char content:"<<"\t"<<pack.GetHeader()->VERSION<<endl;
	}
}
