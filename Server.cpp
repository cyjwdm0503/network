#include "./socks.h"
#include "./Server.h"

CServiceName* CServer::GetClient(int clientfd)
{

  if (m_clientmap.find(clientfd) != m_clientmap.end())
  {
    return m_clientmap[clientfd];
  }
  else
    return NULL;
}

void CServer::AddClient(int fd)
{
  //m_clientmap[fd] = CreateService(fd);
}



