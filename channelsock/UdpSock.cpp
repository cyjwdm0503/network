#include "UdpSock.h"
#include "Log.h"
#include "UdpChannel.h"
#include <string>
CUdpSock::CUdpSock( void ):CInetSock()
{
	m_channel = NULL;
}

CUdpSock::CUdpSock( const char* location ):CInetSock(location)
{
	m_channel =  NULL;
}

CUdpSock::CUdpSock(const CServiceName* service ):CInetSock(service)
{

}

CUdpSock::~CUdpSock()
{
	;
}

int CUdpSock::CreateSocket()
{
	int re = CInetSock::CreateSocket();
	int on = 1;
	setsockopt(m_fd,SOL_SOCKET,SO_BROADCAST,(char*)&on,sizeof(on));
#ifdef WIN32
	/*
	用于解决发送UDP报文到不可达的UDP服务器时会返回-1的错误错误代码10054
	*/
	BOOL bNewBehavior = FALSE;
	DWORD dwBytesReturned = 0;
	DWORD status;
	status = WSAIoctl(m_fd, SIO_UDP_CONNRESET,
		&bNewBehavior, sizeof(bNewBehavior),
		NULL, 0, &dwBytesReturned,
		NULL, NULL);

#endif

	AddChannel(m_fd,m_service);
	return re;

}

int CUdpSock::Connect( CServiceName* server )
{
	/*
	sockaddr_in addr ;
	addr.sin_addr.s_addr = server->GetNHost();
	addr.sin_family = AF_INET;
	addr.sin_port = server->GetNPort();
	socklen_t len = sizeof(addr);
	int re = connect(m_fd,(sockaddr*)&addr,len);
	DEBUGOUT(re);
	CLog::GetInstance()->Printerrno(re);
	return re;
	*/
	/*
	UDP广播时，不再绑定客户端的IP，，否则客户端,和服务器只能接收目的地址=已经绑定的IP的数据包。
	*/
	Bind();
	if(m_channel == NULL)
		m_channel = new CUdpChannel(m_fd);
	m_channel->SetService(*server);
	
	/*UDP 不需要验证是否能够连接上服务器
	char buf[2] = "0";
	int re = m_channel->Write(2,buf);
	if(re <= 0 )
	{
		m_channel =  NULL;
	}
	*/
	return 0;
}

int CUdpSock::Accept()
{
	if(m_channel == NULL)
		m_channel = new CUdpChannel(m_fd);

	CServiceName service;
	service.SetPort(m_service->GetPort()+1);
	service.SetHost(m_service->GetHost());
	service.SetChannel(m_service->GetChannel());
	m_channel->SetService(service);
	return 0;
	/* UDP不需要验证服务器是否有客户连接上
	sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	socklen_t len = sizeof(addr);
	size_t max=1024;
	char buf[1024];
	int re =  recvfrom(m_fd,buf,max,0,(sockaddr*)&addr,&len);
	CServiceName service;
	service.SetSockaddr_in(addr);
	m_channel->SetService(service);
	if(re <= 0)
	{
		delete m_channel;
		m_channel = NULL;
		return -1;
	}
	//AddChannel(m_fd,server);
	return 0;
	*/
}

int CUdpSock::Listen()
{
	return Bind();
	return 0;
}

CChannel* CUdpSock::GetChannel( int fd )
{
	return m_channel;
}

int CUdpSock::Bind()
{
	sockaddr_in addr;
	addr.sin_addr.s_addr =htonl(INADDR_ANY);//  m_service->GetNHost();
	addr.sin_family = AF_INET;
	addr.sin_port =  m_service->GetNPort();
	socklen_t len =  sizeof(addr);
	int re = bind(m_fd,(sockaddr*)&addr,len);
	DEBUGOUT(re);
	return re;
}

CChannel* CUdpSock::AddChannel( int fd,const CServiceName* service/*= NULL*/ )
{
	if(m_channel == NULL)
		m_channel = new CUdpChannel(fd);
	m_channel->SetService(*service);
	return m_channel;
}

