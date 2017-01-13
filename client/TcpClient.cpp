#include "TcpClient.h"
#include "TcpSock.h"

CChannel* CTcpClient::CreateClient( CServiceName* server )
{
	m_clientsock =  new CTcpSock(server);
	m_clientsock->CreateSocket();
	return m_clientsock->GetChannel(m_clientsock->Getfd());
}

CChannel* CTcpClient::CreateClient( const char* location )
{
	m_clientsock =  new CTcpSock(location);
	m_clientsock->CreateSocket();
	return m_clientsock->GetChannel(m_clientsock->Getfd());
}

CChannel* CTcpClient::ConnectServer(const char* location)
{
	CServiceName* name = new CServiceName(location);
	int re = m_clientsock->Connect(name);
	if(re == 0)
	{
		return m_clientsock->GetChannel(m_clientsock->Getfd());
	}
	else
	{
		return NULL;
	}
}
