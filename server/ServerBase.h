#ifndef USERDEFINE_SERVERBASE_H
#define USERDEFINE_SERVERBASE_H

#include "Channel.h"
#include "ServiceName.h"

class CServerBase
{
public:
    CServerBase(){};
    virtual CChannel* CreateServer(CServiceName* server){return NULL;};
    virtual CChannel* CreateServer(const char* location){return NULL;};
    virtual CChannel* AcceptClient(){return NULL;};
};

#endif // SERVERBASE_H
