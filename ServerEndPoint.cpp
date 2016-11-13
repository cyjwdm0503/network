#include "Server.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(int argi ,char*args[])
{
  if (argi < 2)
  {
    cout<<"usage: "<<args[0] << " channel://serverip:port"<<endl;
    exit(-1);
  }
  CServerBase* server = new CTcpServer();//// client(args[1])
  server->CreateServer(args[1]);
  CChannel*  channel = server->AcceptClient();
  char data[1024];
  int over = false;
  while(!over)
  {
        int re = channel->Read(1024,data);
        if(re > 0 )
        {
             cout<<"recive from client:"<<data<<endl;
             over =  true;
        }
        channel->Write(7,"8765432");
  }

  return 0;
}
