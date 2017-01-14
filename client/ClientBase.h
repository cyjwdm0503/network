#ifndef CLIENTBASE_H
#define CLIENTBASE_H

#include "Channel.h"
#include "ServiceName.h"

class CClientBase
{
public:
	CClientBase(){};
	virtual CChannel* CreateClient(CServiceName* server){return NULL;};
	virtual CChannel* CreateClient(const char* location){return NULL;};
	virtual CChannel* ConnectServer(const char* location){return NULL;};
};

#endif // SERVERBASE_H
