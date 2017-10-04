/**
对外提供的updsock 由CInetSock继承而来
**/
#ifndef UDPSOCK_H
#define UDPSOCK_H

#include "InetSock.h"


class CUdpSock:public CInetSock
{

public:
	CUdpSock(void);
	CUdpSock(const char* location);
	CUdpSock(const CServiceName* service);
	virtual ~CUdpSock();
	virtual  CChannel* GetChannel(int fd);
private:
	virtual CChannel* AddChannel(int fd,const CServiceName* service= NULL);
	CChannel* m_channel;

public:
	virtual int CreateSocket();
	virtual int Connect(CServiceName* server);
	virtual int Accept();
	virtual int Bind();
	virtual int Listen();
};


#endif
