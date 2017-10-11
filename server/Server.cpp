#include "Server.h"
#include "UdpSock.h"
#include "TcpSock.h"
CChannel* CServer::CreateServer(CServiceName* server)
{
    m_serversock =  CreateInetSock(server->GetLocation());
    m_serversock->CreateSocket();
	m_serversock->Listen();
    return m_serversock->GetChannel(m_serversock->Getfd());
}

CChannel* CServer::CreateServer(const char* server)
{
    m_serversock =  CreateInetSock(server);
    m_serversock->CreateSocket();
	m_serversock->Listen();
    return m_serversock->GetChannel(m_serversock->Getfd());
}

CChannel* CServer::AcceptClient()
{
    int fd = m_serversock->Accept();
    if(fd >= 0)
        return m_serversock->GetChannel(fd);
    return NULL;
}

CInetSock* CServer::CreateInetSock( const char* location )
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

