#include "Server.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "channelpackage.h"
#include "ServerApi.h"
using namespace std;


#ifdef SERVER

int main(int argi ,char*args[])
{
#ifdef WIN32
	argi = 3;
	args[0] = "server.exe" ;
	args[1] = "udp://127.0.0.1:1234" ;


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
 
	CServerApi server(args[1]);
	server.Create();
	server.Join();
	/*
	CServerBase* server = new CServer();//// client(args[1])
	server->CreateServer(args[1]);
	CChannel*  channel = server->AcceptClient();
	char data[1024];
	int over = false;
	int times=0;
	while(!over)
	{
		char* buf =  new char[1024+1];
		CChannelPackage package(CHANNELPACKAGE_ID,1024);
		int re = package.ReadFromChannel(channel);
		if(re > 0 )
		{
			CPackage pack(PACKAGE_ID);
			package.PopPackage(&pack);
			pack.MakePackage();
			cout<<"CClientApi::HandleInput:"<<re<<" char content:"<<"\t"<<pack.GetHeader()->VERSION<<endl;

			//strncpy(buf,data,re);
			memcpy(buf,package.GetPackagePtr(),re);
			if(times == 20)
				over =  true;
			times++;
			Sleep(1000);
			channel->Write(re,buf);
		}
		
	}
	channel->Disconnect();
	*/
	cout<<"input char:";
	char x;
	cin>>x;
	return 0;
}


#endif
