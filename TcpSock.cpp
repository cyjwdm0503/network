#include "./TcpSock.h"
CTcpSock::CTcpSock():CInetSock()
{
  ;
}

CTcpSock::CTcpSock(char* loc):CInetSock(loc)
{
  ;
}
CTcpSock::CTcpSock(CServiceName* service):CInetSock(service)
{
  ;
}

CTcpSock::~CTcpSock()
{
  ;
}

int CTcpSock::CreateSocket()
{
  CInetSock::CreateSocket(); 
  sockaddr_in addr;
  addr.sin_port = m_service->GetNPort();
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = m_service->GetNHost();
  socklen_t size ;
  size = sizeof(addr);
  return bind(m_fd,(sockaddr*)&addr,size);

}

int CTcpSock::Connect(CServiceName* server)
{

  sockaddr_in addr;
  addr.sin_port = server->GetNPort();
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = server->GetNHost();
  socklen_t addrlen = sizeof(addr);
  return  connect(m_fd,(sockaddr*)&addr,addrlen);

}

int CTcpSock::Accept()
{
  sockaddr_in clientaddr;
  socklen_t addrlen =  sizeof(clientaddr);
  int fd = accept(m_fd,(sockaddr*)&clientaddr,&addrlen);
  return fd;
  //return 0;
}

int CTcpSock::Listen()
{
  return listen(m_fd,SOCK_STREAM);
}
