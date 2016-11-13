#ifndef SERVER_H
#define SERVER_H

#include "./socks.h"
#include "./ServiceName.h"
#include <map>
#include "ServerBase.h"
using namespace std;
class CTcpServer:public CServerBase
{
    virtual CChannel* CreateServer(CServiceName* server);
    virtual CChannel* CreateServer(const char* location);
    virtual CChannel* AcceptClient();
public:
    CInetSock* m_serversock;
};




#endif


