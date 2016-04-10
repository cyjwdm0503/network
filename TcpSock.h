#ifndef TCPSOCK_H
#define TCPSOCK_H

#include "./InetSock.h"


class CTcpSock:public CInetSock
{

public:
  CTcpSock(void);
  CTcpSock(char* location);
  CTcpSock(CServiceName* service);
  virtual ~CTcpSock();

  virtual int CreateSocket();
  virtual int Connect(CServiceName* server);
  virtual int Accept();
private:
  CServiceName* m_service;
  int m_fd;
};


#endif
