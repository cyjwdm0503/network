#include "TcpSock.h"
#include "Log.h"
CTcpSock::CTcpSock():CInetSock()
{
	;
}

CTcpSock::CTcpSock(const char* loc):CInetSock(loc)
{
	;
}
CTcpSock::CTcpSock(const CServiceName* service):CInetSock(service)
{
	;
}

CTcpSock::~CTcpSock()
{
	;
}

int CTcpSock::CreateSocket()
{
	int re = CInetSock::CreateSocket();
	AddChannel(m_fd,m_service);
	return re;
}

int CTcpSock::Connect(CServiceName* server)
{

	sockaddr_in addr;
	addr.sin_port = server->GetNPort();
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = server->GetNHost();
    CLog::GetInstance()->PrintLog("addr:%d,port:%d",addr.sin_addr.s_addr,addr.sin_port);
	socklen_t addrlen = sizeof(addr);
	int re =   connect(m_fd,(sockaddr*)&addr,addrlen);
	DEBUGOUT(re);
	CLog::GetInstance()->Printerrno(re);
	return re;
}

int CTcpSock::Accept()
{
	sockaddr_in clientaddr;
	socklen_t addrlen =  sizeof(clientaddr);
	int fd = accept(m_fd,(sockaddr*)&clientaddr,&addrlen);
    CLog::GetInstance()->PrintLog("addr:%d,port:%d",clientaddr.sin_addr.s_addr,clientaddr.sin_port);
	if(fd == -1)
	{
		DEBUGOUT(-1);
		//exit(-1);
		return -1;
	}
	CServiceName service;
	service.SetSockaddr_in(clientaddr);
	AddChannel(fd,&service);
	return fd;
	//return 0;
}

int CTcpSock::Listen()
{
	Bind();
	int re =  listen(m_fd,SOCK_STREAM);
	// CLog::GetInstance()->Printerrno(re);
	DEBUGOUT(re);
	return re;
}

int CTcpSock::Bind()
{
	sockaddr_in addr;
	addr.sin_port = m_service->GetNPort();
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = m_service->GetNHost();
	socklen_t addr_size ;
	addr_size = sizeof(addr);
    CLog::GetInstance()->PrintLog("addr:%d,port:%d",addr.sin_addr.s_addr,addr.sin_port);
	int re = bind(m_fd,(sockaddr*)&addr,addr_size);
	DEBUGOUT(re);
	return re;
}


