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
	#ifdef WIN32
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
		DEBUGOUT(re);
		int errnum = GET_LAST_ERROR();
		if(errnum == EWOULDBLOCK)
			return 0;

		DEBUGOUT(re);
		CLog::GetInstance()->Printerrno(re);
	}


}

int CChannel::Write(size_t max,const char* buf)
{
	if(!m_bConnected)
		return -1;
	int re = 0;
	#ifdef WIN32
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
		DEBUGOUT(re);
		int errnum = GET_LAST_ERROR();
		if(errnum == EWOULDBLOCK)
			return 0;

		DEBUGOUT(re);
		CLog::GetInstance()->Printerrno(re);
	}


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

}

bool CChannel::Available()
{
	return m_bConnected;
}

bool CChannel::Disconnect()
{
	m_bConnected = false;
	std::cout<<"CChannel::Disconnect()"<<std::endl;
#ifdef WIN32
  closesocket(m_fd);
#else
  close(m_fd);
#endif
	return m_bConnected;
}
