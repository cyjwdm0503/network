#include "UdpChannel.h"


int CUdpChannel::Write( size_t max ,const char* buf )
{
	sockaddr_in addr;
	addr.sin_addr.s_addr = GetService()->GetNHost();
	addr.sin_port = GetService()->GetNPort();
	addr.sin_family = AF_INET;
	socklen_t len = sizeof(addr);
	int re =  sendto(m_fd,buf,max,0,(sockaddr*)&addr,len);
	return re;
}

int CUdpChannel::Read( size_t max ,char* buf )
{
	sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	//addr.sin_addr.s_addr = GetService()->GetNHost();
	//addr.sin_port = GetService()->GetNPort();
	//addr.sin_family = AF_INET;
	socklen_t len = sizeof(addr);
	int re =  recvfrom(m_fd,buf,max,0,(sockaddr*)&addr,&len);
	//CServiceName service;
	//service.SetSockaddr_in(addr);
	//SetService(service);
	return re;
}

CUdpChannel::CUdpChannel( int fd ):CChannel(fd)
{
	;//CChannel(fd);
}
