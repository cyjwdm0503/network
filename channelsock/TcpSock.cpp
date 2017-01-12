#include "TcpSock.h"
#include "Log.h"
CTcpSock::CTcpSock():CInetSock()
{
  ;
}

CTcpSock::CTcpSock(const char* loc):CInetSock(loc)
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
  socklen_t addr_size ;
  addr_size = sizeof(addr);
  int re = bind(m_fd,(sockaddr*)&addr,addr_size);
  AddChannel(m_fd,m_service);
  DEBUGOUT(re);
  return re;
}

int CTcpSock::Connect(CServiceName* server)
{

  sockaddr_in addr;
  addr.sin_port = server->GetNPort();
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = server->GetNHost();
  socklen_t addrlen = sizeof(addr);
  int re =   connect(m_fd,(sockaddr*)&addr,addrlen);
  DEBUGOUT(re);
 // CLog::GetInstance()->Printerrno(re);
  return re;
}

int CTcpSock::Accept()
{
    Listen();
  sockaddr_in clientaddr;
  socklen_t addrlen =  sizeof(clientaddr);
  int fd = accept(m_fd,(sockaddr*)&clientaddr,&addrlen);
  if(fd == -1)
  {
      DEBUGOUT(-1);
      exit(-1);
  }
  CServiceName service;
  service.SetSockaddr_in(clientaddr);
  AddChannel(fd,&service);
  return fd;
  //return 0;
}

int CTcpSock::Listen()
{
  int re =  listen(m_fd,SOCK_STREAM);
 // CLog::GetInstance()->Printerrno(re);
  DEBUGOUT(re);
  return re;
}


