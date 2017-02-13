#include "ClientApi.h"
#include <iostream>
#include "Client.h"
#include "channelpackage.h"
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

	CChannelPackage package(CHANNELPACKAGE_ID,MAXLENGTH);

	if(m_clientchannel != NULL)
	{
		int len = package.ReadFromChannel(m_clientchannel);
		//int len = m_clientchannel->Read(package.GetValidLength(),package.GetValidDataPtr());
		if(len > 0)
			cout<<"package:len"<<package.GetPackageLen();
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


		m_leavewritelen = len;

		CPackage pack(PACKAGE_ID);
		package.PopPackage(&pack);
		pack.MakePackage();
		cout<<"CClientApi::HandleInput:"<<len<<"fp"<<m_clientchannel->Getfd()<<" char content:"<<"\t"<<pack.GetHeader()->VERSION<<endl;
	}
}

void CClientApi::HandleOupt()
{
	CChannelPackage package(CHANNELPACKAGE_ID,MAXLENGTH);
	CPackage pack(PACKAGE_ID,MAXLENGTH);
	pack.GetHeader()->VERSION = ++CLIENTVERSION;
	pack.PushHeader();
	package.PushPackage(&pack);
	if(m_clientchannel != NULL)
	{
		int len = m_clientchannel->Write(package.GetPackageLen(),package.GetPackagePtr());
		m_leavewritelen = 0;
		cout<<"package:len"<<package.GetPackageLen()<<"CClientApi::HandleOupt:"<<len<<"fp"<<m_clientchannel->Getfd()<<" char content:"<<"\t"<<pack.GetHeader()->VERSION<<endl;
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

