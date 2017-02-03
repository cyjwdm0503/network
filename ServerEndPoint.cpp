#include "Server.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;


#ifdef SERVER

int main(int argi ,char*args[])
{
#ifdef WIN32
	argi = 3;
	args[0] = "server.exe" ;
	args[1] = "tcp://127.0.0.1:1234" ;


	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	if (argi < 2)
	{
		cout<<"usage: "<<args[0] << " channel://serverip:port"<<endl;
		exit(-1);
	}
#else

#endif
 

	CServerBase* server = new CServer();//// client(args[1])
	server->CreateServer(args[1]);
	CChannel*  channel = server->AcceptClient();
	char data[1024];
	int over = false;
	int times=0;
	while(!over)
	{
		int re = channel->Read(1024,data);
		if(re > 0 )
		{
			char* buf =  new char[re+1];
			strncpy(buf,data,re);
			buf[re] = '\0';
			cout<<"recive from client:"<<buf<<endl;
			if(times == 20)
				over =  true;
			times++;
			Sleep(1000);
		}
		channel->Write(7,"8765432");
	}
	cout<<"input char:";
	char x;
	cin>>x;
	return 0;
}


#endif
