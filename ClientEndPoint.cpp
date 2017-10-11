#include "ClientApi.h"
#include "Log.h"

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>



#ifdef WIN32



#else
	#include <csignal>
#endif
using namespace std;

#ifdef CLIENT

struct Content
{
	int m_value;
	int m_ratio;
	int m_buf;
};


int main(int argi ,char*args[])
{



	if( argi != 3)
	{
		argi = 3;
		args[0] = "client.exe" ;
#ifdef TCP
		args[1] = "tcp://127.0.0.1:4321" ;
		args[2] = "tcp://127.0.0.1:1234" ;
#endif
#ifdef UDP
		args[1] = "udp://127.255.255.255:1235" ;
		args[2] = "udp://127.255.255.255:1234" ;
#endif
	}
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
	//signal(SIGABRT,SIG_IGN);
	signal(SIGPIPE,SIG_IGN);
	//signal(SIGINT,SIG_IGN);
#endif
	
	ClientApp client(args[1],args[2]);
	client.Create();
	client.Join();
	/*
	if (argi < 3)
	{
	cout<<"usage: "<<args[0] << "channel:://clientip:port channel://serverip:port"<<endl;
	exit(-1);
	}
	CClient client;
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

	*/
	cout<<"input char:";
	char x;
	cin>>x;
	return 0;
}

#endif
