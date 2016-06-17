#ifndef INETSOCK_H
#define INETSOCK_H

#include "socks.h"
#include "./ServiceName.h"

class CInetSock
{
public:
  CInetSock(void);
  CInetSock(char* location);
  CInetSock(CServiceName* service);
  virtual ~CInetSock();

  virtual int CreateSocket();
  virtual int Connect(CServiceName* server){};
  virtual int Accept(){};
protected:
  CServiceName* m_service;
  int m_fd;
};


#endif
