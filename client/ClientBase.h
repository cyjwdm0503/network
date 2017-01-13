#ifndef CLIENTBASE_H
#define CLIENTBASE_H

#include "TcpSock.h"
class CClientBase
{
public:
	CClientBase(){};
	virtual CChannel* CreateClient(CServiceName* server){return NULL;};
	virtual CChannel* CreateClient(const char* location){return NULL;};
	virtual CChannel* ConnectServer(const char* location){return NULL;};
};

#endif // SERVERBASE_H
