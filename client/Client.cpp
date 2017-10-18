﻿#include "Client.h"
#include "TcpSock.h"
#include "UdpSock.h"
#include "Log.h"
CChannel* CClient::CreateClient( CServiceName* server )
{
	m_clientsock =  CreateInetSock(server->GetLocation());
	m_clientsock->CreateSocket();
	return m_clientsock->GetChannel(m_clientsock->Getfd());
}

CChannel* CClient::CreateClient( const char* location )
{
	m_clientsock =  CreateInetSock(location);
	m_clientsock->CreateSocket();
	return m_clientsock->GetChannel(m_clientsock->Getfd());
}

CChannel* CClient::ConnectServer(const char* location)
{
	CServiceName* name = new CServiceName(location);
	int re = m_clientsock->Connect(name);
	if(re == 0)
	{
		return m_clientsock->GetChannel(m_clientsock->Getfd());
	}

	/*处理在非阻塞模式下返回-1的缺陷*/
	fd_set connectfd;
	FD_ZERO(&connectfd);
	timeval tv;
	tv.tv_sec= 10;
	tv.tv_usec = 0;
	FD_SET(m_clientsock->Getfd(),&connectfd);
	re = select(m_clientsock->Getfd()+1,NULL,&connectfd,NULL,&tv);
	DEBUGOUT(re);
	if(re <= 0)
	{
#ifdef WIN
		closesocket(m_clientsock->Getfd());
#else
		close(m_clientsock->Getfd());
#endif
		re = -1;
	}

	//if(GET_LAST_ERROR() != 0)
	//	return NULL;

	if(re!= 0 && FD_ISSET(m_clientsock->Getfd(),&connectfd))
	{
		sockaddr_in addr;
		socklen_t len = sizeof(addr);
		if(getpeername(m_clientsock->Getfd(),(sockaddr*)&addr,&len)<0)
			re = -1;
		else
			re = 0;
	}

	if(re == 0)
	{
		return m_clientsock->GetChannel(m_clientsock->Getfd());
	}
	else
	{
		return NULL;
	}
}

CInetSock* CClient::CreateInetSock( const char* location )
{
	CServiceName service(location);
	switch(service.GetNChannel())
	{
	case SOCK_STREAM:
		return new CTcpSock(location);
		break;
	case SOCK_DGRAM:
		return new CUdpSock(location);
		break;
	default:
		return new CTcpSock(location);
		break;
	}

	return NULL;

}
