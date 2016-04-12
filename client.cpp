#include "TcpSock.h"
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
  return 0;
}
