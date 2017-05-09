#include "Log.h"
#include "UdpChannel.h"
#include <unistd.h>

int CUdpChannel::Write( size_t max ,const char* buf )
{
	if(!m_bConnected)
		return -1;
	sockaddr_in addr;
	addr.sin_addr.s_addr = GetService()->GetNHost();
	addr.sin_port = GetService()->GetNPort();
	addr.sin_family = AF_INET;
	socklen_t len = sizeof(addr);
	int re =  sendto(m_fd,buf,max,0,(sockaddr*)&addr,len);
	if(re == 0)
	{
		return -1;
	}
	if(re == -1)
	{
		int errnum = GET_LAST_ERROR();
		if(errnum == EWOULDBLOCK)
			return 0;

		DEBUGOUT(re);
		CLog::GetInstance()->Printerrno(re);
	}
	return re;
}

int CUdpChannel::Read( size_t max ,char* buf )
{
	if(!m_bConnected)
		return -1;
	sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	//addr.sin_addr.s_addr = GetService()->GetNHost();
	//addr.sin_port = GetService()->GetNPort();
	//addr.sin_family = AF_INET;
	socklen_t len = sizeof(addr);
	int re =  recvfrom(m_fd,buf,max,0,(sockaddr*)&addr,&len);
	if(re ==0)
	{
		return -1;
	}
	if(re == -1)
	{
		int errnum = GET_LAST_ERROR();
		if(errnum == EWOULDBLOCK)
			return 0;

		//注意在UDP发送第一个数据时，且没有UDP服务器时，能select 时收到-1的结果
		/*10054
		https://support.microsoft.com/zh-cn/help/263823/winsock-recvfrom-now-returns-wsaeconnreset-instead-of-blocking-or-timing-out
		*/
		DEBUGOUT(re);
		CLog::GetInstance()->Printerrno(re);
	}
	//CServiceName service;
	//service.SetSockaddr_in(addr);
	//SetService(service);
	return re;
}

CUdpChannel::CUdpChannel( int fd ):CChannel(fd)
{
	int rcvbufsize = 1*1024*1024;
	socklen_t paramlen = sizeof(rcvbufsize);
	int ret = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (const char *)&rcvbufsize, paramlen);
	if(ret != 0)
	{
		CLog::GetInstance()->PrintLog("Can not setsockopt revbuf\n");
	}

#ifdef WIN32
	unsigned long on_windows=1;
	ret = ioctlsocket(fd, FIONBIO, &on_windows) ; 
#else
	int on=1;
	ret = ioctl(fd, FIONBIO, (char *)&on);
#endif
	if(ret != 0)
	{
		CLog::GetInstance()->PrintLog("Can not setsockopt FIONBIO\n");
	}
	;//CChannel(fd);
}
