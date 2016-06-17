#include "./InetSock.h"
#include "./Log.h"

CInetSock::CInetSock(void)
{
  m_service =  new CServiceName("");
}

CInetSock::CInetSock(char* location)
{
  m_service = new CServiceName(location);
}

CInetSock::CInetSock(CServiceName* service)
{
  m_service = service;
}

CInetSock::~CInetSock()
{
  if(m_service != NULL)
    delete m_service;
  m_service = NULL;
}

int CInetSock::CreateSocket()
{
  m_fd = socket(AF_INET,m_service->GetNChannel(),0);
  DEBUGOUT(m_fd);
  return m_fd;
}

