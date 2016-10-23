#ifndef SERVER_H
#define SERVER_H

#include "./socks.h"
#include "./ServiceName.h"
#include <map>
using namespace std;
class CServer
{
public:
  CServiceName* GetClient(int clientfd);
  void AddClient(int fd);
protected:
  map<int,CServiceName*> m_clientmap;


};




#endif


