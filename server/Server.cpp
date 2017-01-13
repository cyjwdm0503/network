#include "./socks.h"
#include "./Server.h"

CChannel* CTcpServer::CreateServer(CServiceName* server)
{
    m_serversock =  new CTcpSock(server);
    m_serversock->CreateSocket();
    return m_serversock->GetChannel(m_serversock->Getfd());
}

CChannel* CTcpServer::CreateServer(const char* server)
{
    m_serversock =  new CTcpSock(server);
    m_serversock->CreateSocket();
	m_serversock->Listen();
    return m_serversock->GetChannel(m_serversock->Getfd());
}

CChannel* CTcpServer::AcceptClient()
{
    int fd = m_serversock->Accept();
    return m_serversock->GetChannel(fd);
}

