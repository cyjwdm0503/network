#ifndef CLIENT_H
#define CLIENT_H

#include "ClientBase.h"
#include "InetSock.h"

using namespace std;
class CClient:public CClientBase
{
public:
	virtual CChannel* CreateClient(CServiceName* server);
	virtual CChannel* CreateClient(const char* location);
	virtual CChannel* ConnectServer(const char* location);
public:
	CInetSock* m_clientsock;
	CInetSock* CreateInetSock(const char* servicename);

};

#endif


