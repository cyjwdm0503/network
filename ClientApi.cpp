#include "ClientApi.h"
#include <iostream>
#include "Client.h"
#include "channelpackage.h"
#include "contentpackage.h"
#include "applicationpackage.h"
#include "packagedefine.h"
#include "fielddefine.h"
#include "Log.h"
using namespace  std;

static  int CLIENTVERSION = 0;
static char letter = 'a';
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
	if(!m_clientchannel->Available())
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


	CChannelPackage channelpackage(4096);
	if(m_clientchannel != NULL)
	{
		int len = channelpackage.ReadFromChannel(m_clientchannel);
		//int len = m_clientchannel->Read(package.GetValidLength(),package.GetValidDataPtr());
		if(len > 0)
			cout<<"package:len"<<channelpackage.Length();
		else if(len <0 )
		{
			m_clientchannel->Disconnect();
			return ;
		}
		else
		{
			cout<<"CClientApi::HandleInput:"<<len<<"fp"<<m_clientchannel->Getfd()<<" char content:"<<"\t"<<endl;
			return;
		}


		//m_leavewritelen = len;
		//从channelpackage中取出来对应的contentpackage
		CContentPackage contentpackage;
		contentpackage.AddBuf(&channelpackage);
		if(contentpackage.ValidPackage()>0)
			cout<<"package:len"<<channelpackage.Length()<<"CClientApi::HandleInput:"<<len<<"fp"<<m_clientchannel->Getfd()<<" char content:"<<"\t"<<contentpackage.GetContentHeader()->Type<<endl;
	}
}

void CClientApi::HandleOutput()
{
	CContentPackage contentpackage;
	contentpackage.ConstructAlloc(1024,128);
	contentpackage.AllocMax();
	contentpackage.GetContentHeader()->Type = ++ CLIENTVERSION;
	contentpackage.MakePackage();

	CChannelPackage channelpackage(4096);
	channelpackage.AddBuf(&contentpackage);
	channelpackage.MakePackage();

	if(m_clientchannel != NULL)
	{
		int len = m_clientchannel->Write(channelpackage.Length(),channelpackage.Address());
		m_leavewritelen = 0;
		cout<<"package:len"<<channelpackage.Length()<<"CClientApi::HandleOupt:"<<len<<"fp"<<m_clientchannel->Getfd()<<" char content:"<<"\t"<<contentpackage.GetContentHeader()->Type<<endl;
	}
}

CClientApi::CClientApi( const char* clientip,const char* serverip ):CHandler(this),m_clientchannel(NULL)
{
	AddHandler(this);
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


bool CClientSession::InitInstance()
{
	if(m_clientchannel != NULL)
	{
		m_Session = new CClientContent(this,m_clientchannel);
		AddHandler(m_Session);
		return CDispatcher::InitInstance();
	}
	return false;
}

CClientSession::CClientSession( const char* clientip,const char* serverip )
{
	m_client = new CClient();
	m_client->CreateClient(clientip);
	m_clientchannel = m_client->ConnectServer(serverip);
}


CClientApplicationSession::CClientApplicationSession(CDispatcher* dispatcher,CChannel* channel):
	CApplicationSession(dispatcher,channel)
{
	;
}

int CClientApplicationSession::HandlePackage( CPackage* pPackage)
{
	try
	{
		CApplicationPackage* content = dynamic_cast<CApplicationPackage*>(pPackage);
		int i=0;
		if(content != NULL)
		{
			cout<<"recv applicationpackage from server;seqnum:"<<content->GetSequenceNo()<<endl;
			if(content->GetTid()== PACKAGE_SendField_ID)
			{
				SendField field;;
				content->GetSingleField(&field.m_Describe,&field);
				cout<<"recv send Field from server:"<<endl;
				cout<<field.m_char<<"\t"<<field.m_int<<"\t"<<field.m_string<<"\t"<<field.m_short<<endl;
			}
		}
	}
	catch(exception &e)
	{
		CLog::GetInstance()->PrintLog(e.what());
	}
	return 0;
}


ClientApp::ClientApp( const char* client, const char* server )
{
	m_client = new CClient();
	m_client->CreateClient(client);
	m_clientchannel = m_client->ConnectServer(server);
}

bool ClientApp::InitInstance()
{
	if(m_clientchannel != NULL)
	{

		m_Session = new CClientApplicationSession(this,m_clientchannel);
		AddHandler(m_Session);
		return CDispatcher::InitInstance();

	}
	return false;
}

