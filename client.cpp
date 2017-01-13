#include "TcpSock.h"
#include "TcpClient.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;


int main(int argi ,char*args[])
{
	argi = 3;
	args[0] = "netword_ini.exe" ;
	args[1] = "tcp://127.0.0.1:4321" ;
	args[2] = "tcp://127.0.0.1:1234" ;

#ifdef WIN32

	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
#else

#endif
	if (argi < 3)
	{
		cout<<"usage: "<<args[0] << "channel:://clientip:port channel://serverip:port"<<endl;
		exit(-1);
	}
	CTcpClient client;
	client.CreateClient(args[1]);
	CChannel* channel = client.ConnectServer(args[2]);
	if(channel == NULL)
		return 0;
	char data[] = "1234455678";
	channel->Write(strlen(data),data);
	bool over = false;
	while(!over)
	{
		int re = channel->Read(1024,data);
		if(re > 0 )
		{
			char* buf =  new char[re+1];
			strncpy(buf,data,re);
			buf[re+1] = '\0';
			cout<<"recive from server:"<<buf<<endl;
			over =  true;
		}
	}
	return 0;
}
