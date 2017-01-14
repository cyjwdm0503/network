/**
对外提供的tcpsock 由CInetSock继承而来
**/
#ifndef TCPSOCK_H
#define TCPSOCK_H

#include "InetSock.h"


class CTcpSock:public CInetSock
{

public:
  CTcpSock(void);
  CTcpSock(const char* location);
  CTcpSock(const CServiceName* service);
  virtual ~CTcpSock();


  virtual int CreateSocket();
  virtual int Connect(CServiceName* server);
  virtual int Accept();
  virtual int Listen();
};


#endif
