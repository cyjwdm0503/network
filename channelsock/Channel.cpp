#include <iostream>
#include "Channel.h"
#include "Log.h"
CChannel::~CChannel()
{
	if(m_service != NULL)
	{
		delete m_service;
		m_service =  NULL;
	}
}

int CChannel::Read(size_t max,char* buf)
{
	if(!m_bConnected)
		return -1;
	int re = 0;
	#ifdef WIN
	re = recv(m_fd,buf,max,0);
	#else
	re =  read(m_fd,buf,max);
	#endif // WINDOWS

	if(re == 0)
	{
		return -1;
	}
	if(re == -1)
	{
		
		int errnum = GET_LAST_ERROR();
		if(errnum == EWOULDBLOCK)
			return 0;
		else
		{
			DEBUGOUT(re);
			return -1;
		}
	}
    
    char logbuf[max+1];
    memcpy(logbuf, buf, re);
    char format[128];
    sprintf(format, "\%%%ds",re);
    CLog::GetInstance()->PrintLog(format,buf);
    
	return re;
}

int CChannel::Write(size_t max,const char* buf)
{
	if(!m_bConnected)
		return -1;
	int re = 0;
	#ifdef WIN
	re = send(m_fd,buf,max,0);
	#else
	re = write(m_fd,buf,max);
	#endif // WINDOWS

	if(re == 0)
	{
		return -1;
	}
	if(re == -1)
	{
		
		int errnum = GET_LAST_ERROR();
		if(errnum == EWOULDBLOCK)
			return 0;
		else
		{

			DEBUGOUT(re);
			return -1;
		}
	}
    
    char logbuf[max+1];
    memcpy(logbuf, buf, re);
    char format[128];
    sprintf(format, "\%%%ds",re);
    CLog::GetInstance()->PrintLog(format,buf);
    
	return re;

}

int CChannel::Getfd() const
{
	return m_fd;
}

void CChannel::SetService(const CServiceName& service)
{
	if (m_service == NULL)
		m_service = new CServiceName();
	memcpy(m_service,&service,sizeof(CServiceName));
}

CServiceName* CChannel::GetService()
{
	return m_service;
}


CChannel::CChannel( int fd )
{
	m_fd = fd;
	m_service = NULL;
	m_bConnected = true;
	int ret = 0;

#ifdef WIN
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

}

bool CChannel::Available()
{
	return m_bConnected;
}

bool CChannel::Disconnect()
{
	m_bConnected = false;
	std::cout<<"CChannel::Disconnect()"<<std::endl;
#ifdef WIN
  closesocket(m_fd);
#else
  close(m_fd);
#endif
	return m_bConnected;
}

const char* CChannel::GetRemoteName()
{
	sockaddr_in name;
	socklen_t nameLen = sizeof(sockaddr_in);
	if (getpeername(m_fd,(sockaddr*)&name,&nameLen)==0)
	{
		CServiceName service;
		service.SetSockaddr_in(name);
		return service.GetLocation();
	}
	return NULL;
}
