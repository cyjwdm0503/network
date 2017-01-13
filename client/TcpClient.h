#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "ClientBase.h"

using namespace std;
class CTcpClient:public CClientBase
{
public:
	virtual CChannel* CreateClient(CServiceName* server);
	virtual CChannel* CreateClient(const char* location);
	virtual CChannel* ConnectServer(const char* location);
public:
	CInetSock* m_clientsock;
};

#endif


