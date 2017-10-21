#ifndef USERDEFINE_SERVER_H
#define USERDEFINE_SERVER_H

#include "ServerBase.h"
#include "InetSock.h"
using namespace std;
class CServer:public CServerBase
{
public:
	virtual CChannel* CreateServer(CServiceName* server);
	virtual CChannel* CreateServer(const char* location);
	virtual CChannel* AcceptClient();
protected:
	CInetSock* m_serversock;
	CInetSock* CreateInetSock(const char* servicename);
};




#endif


