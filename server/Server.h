#ifndef SERVER_H
#define SERVER_H

#include "ServerBase.h"
#include "InetSock.h"
using namespace std;
class CServer:public CServerBase
{
public:
	virtual CChannel* CreateServer(CServiceName* server);
	virtual CChannel* CreateServer(const char* location);
	virtual CChannel* AcceptClient();
public:
	CInetSock* m_serversock;
	CInetSock* CreateInetSock(const char* servicename);
};




#endif


