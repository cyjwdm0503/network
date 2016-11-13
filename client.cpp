#include "./TcpSock.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(int argi ,char*args[])
{
  if (argi < 3)
  {
    cout<<"usage: "<<args[0] << "channel:://clientip:port channel://serverip:port"<<endl;
    exit(-1);
  }
  CTcpSock client(args[1]);
  client.CreateSocket();
  CServiceName server(args[2]);
  client.Connect(&server);
  CChannel* channel = client.GetChannel(client.Getfd());
  char data[] = "1234455678";
  channel->Write(strlen(data),data);
  bool over = false;
   while(!over)
  {
    int re = channel->Read(8,data);
    if(re > 0 )
    {
             cout<<"recive from server:"<<data<<endl;
             over =  true;
    }
  }
  return 0;
}


