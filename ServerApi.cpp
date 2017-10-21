#include "ServerApi.h"
#include "channelpackage.h"
#include "contentpackage.h"
#include "contentsession.h"
#include "applicationpackage.h"
#include <iostream>
#include "fielddefine.h"
#include "packagedefine.h"
#include "Log.h"

static int SERVERVERSION = 100;
CServerApi::CServerApi(CServer* server,CChannel* channel,CDispatcher* reactor):CHandler(reactor)
{
	reactor->AddHandler(this);
	//m_server =  new CServer();
	//m_server->CreateServer(server);
	////实际为client与server通信的chanel
	//m_serverchannel = m_server->AcceptClient();
	m_server = server;
	m_serverchannel = channel;
	m_leavewritelen = 4;

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
	CChannelPackage channelpackage(4096);
	if(m_serverchannel != NULL)
	{
		int re = channelpackage.ReadFromChannel(m_serverchannel);
		if(re > 0)
		{
			m_leavewritelen = re;
			cout<<"package:len"<<channelpackage.Length();
		}
		else if(re < 0)
		{//channel在断线后应该通知server.重新进入accept流程。
			m_serverchannel->Disconnect();
			return ;
		}
		else
		{
			cout<<"CServerApi::HandleInput:"<<re<<"fp"<<m_serverchannel->Getfd()<<" char content:"<<"\t"<<endl;
			return ;
		}
		//从channelpackage中取出来对应的contentpackage
		CContentPackage contentpackage;
		contentpackage.AddBuf(&channelpackage);
		if(contentpackage.ValidPackage() >0)
			cout<<"package:len"<<channelpackage.Length()<<"CServerApi::HandleInput:"<<re<<"fp"<<m_serverchannel->Getfd()<<" char content:"<<"\t"<<contentpackage.GetContentHeader()->Type<<endl;

	}
}

void CServerApi::HandleOutput()
{
	CContentPackage contentpackage;
	contentpackage.ConstructAlloc(1024,128);
	contentpackage.AllocMax();
	contentpackage.GetContentHeader()->Type = ++ SERVERVERSION;
	contentpackage.MakePackage();

	CChannelPackage channelpackage(1024);
	channelpackage.AddBuf(&contentpackage);
	channelpackage.MakePackage();
	if(m_serverchannel != NULL)
	{
		int len = m_serverchannel->Write(channelpackage.Length(),channelpackage.Address());
		//m_leavewritelen --;
		cout<<"package:len"<<channelpackage.Length()<<"CServerApi::HandleOupt:"<<len<<"fp"<<m_serverchannel->Getfd()<<" char content:"<<"\t"<<contentpackage.GetContentHeader()->Type<<endl;
	}
}

CServerSession::CServerSession( CSelectReactor* selecter,const char* location ):CServerAcceptManager(selecter,location)
{
	
}

CServerSession::~CServerSession()
{

}

CSession* CServerSession::CreateSession( CChannel* channel )
{
	 
	CServerApplicationSession*  session = new CServerApplicationSession(m_serverreactor,channel);
	m_serverreactor->AddHandler(session);
	return session;
	
}

const int APPLICATIONPACKAGE_TEST_TIMER_ID = 9999;
CServerApplicationSession::CServerApplicationSession( CDispatcher* dispatcher,CChannel* channel )
	:CApplicationSession(dispatcher,channel)
{
	SetTimer(APPLICATIONPACKAGE_TEST_TIMER_ID,10);
}



void CServerApplicationSession::OnTimer( int event )
{
	if(event == APPLICATIONPACKAGE_TEST_TIMER_ID)
	{

		CApplicationPackage contentpackage;
		contentpackage.ConstructAlloc(1024,128);
		contentpackage.AllocMax();
		contentpackage.SetSequenceNo(++SERVERVERSION);
		contentpackage.SetTid(PACKAGE_SendField_ID);
		contentpackage.Truncate(0);
		SendField field;
		field.m_char = 's';
		field.m_int = SERVERVERSION;
		field.m_short = SERVERVERSION;
		field.m_string = "1234567890";
		contentpackage.AddField(&field.m_Describe,&field);
		//contentpackage.MakePackage();

		if(GetProtocol() != NULL)
		{
			int len = GetProtocol()->send(&contentpackage);
			//m_leavewritelen --;
			cout<<"Server send to client applicationpackage:seqnum:" <<  contentpackage.GetSequenceNo()<<endl;

		}
	}
}

int CServerApplicationSession::HandlePackage( CPackage* pPackage )
{
	try
	{
		CApplicationPackage* content = dynamic_cast<CApplicationPackage*>(pPackage);
		int i=0;
		if(content != NULL)
		{
			cout<<"recv applicationpackage from client;seqnum:"<<content->GetSequenceNo()<<endl;
		}
	}
	catch(exception &e)
	{
		CLog::GetInstance()->PrintLog(e.what());
	}
	return 0;
}



void CServerApplicationSession::OnDisconnected(int ErrorCode)
{
	KillTimer(APPLICATIONPACKAGE_TEST_TIMER_ID);	
}