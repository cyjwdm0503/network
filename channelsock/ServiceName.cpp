#include "ServiceName.h"
#include <cstring>
//#include <WinSock2.h>
using namespace std;

CServiceName::CServiceName(const char* location):m_host(),m_port(),m_location(),m_channel()
{
	strncpy(m_location,location,sizeof(m_location));
	int pos = 0;
	int beginpos = 0;
	int endpos = beginpos+1;

	bool bchannel = false;
	bool bhost = false;
	bool bport = false;

	strcpy(m_host,"127.0.0.1");
	strcpy(m_port,"");
	strcpy(m_channel,"tcp");

	while( m_location[pos] != '\0')
	{
		//m_channel
		if(m_location[pos] == ':' && m_location[pos+1] == '/' && bchannel == false )
		{
			strncpy(m_channel,m_location,pos+1);
			m_channel[pos] = '\0';
			bchannel = true;
		}


		//m_host
		if(bchannel == true
			&& m_location[pos] == '/'
			&& m_location[pos-1] == '/'
			&& bhost == false)
		{
			beginpos = pos+1;
		}
		if(bchannel == true
			&& (m_location[pos] == '/' || m_location[pos] == ':')
			&& m_location[pos-1]!= '/'
			&& bhost == false)
		{
			endpos =  pos;
			if(endpos > beginpos && beginpos > 0)
			{
				strncpy(m_host,m_location+beginpos,endpos-beginpos);
				bhost =  true;
				m_host[endpos-beginpos] = '\0';
			}
		}


		//m_port

		if(bhost == true
			&& bport == false
			&& m_location[pos] == ':')
		{
			beginpos = pos+1;
		}
		if(bhost == true
			&& bport == false
			&& (m_location[pos+1] == '\0' || m_location[pos] == '/'))
		{
			if(m_location[pos] != '/' )
				endpos = pos+1;
			else 
				endpos = pos ;
			strncpy(m_port,m_location+beginpos,endpos-beginpos);
			bport = true;
			m_port[endpos-beginpos]= '\0';
		}
		pos++;
	}
}

CServiceName::CServiceName()
{

	m_host[0] = '\0';
	m_port[0] = '\0';
	m_location[0] = '\0';
	m_channel[0] = '\0';
}

CServiceName::CServiceName(const CServiceName& ser )
{
	strncpy(m_host,ser.m_host,sizeof(m_host));
	strncpy(m_port,ser.m_port,sizeof(m_port));
	strncpy(m_location,ser.m_location,sizeof(m_location));
	strncpy(m_channel,ser.m_channel,sizeof(m_channel));
}

channel_t CServiceName::GetNChannel() const
{
	if(strncmp(m_channel,"tcp",3)==0 || strncmp(m_channel,"TCP",3)==0)
		return SOCK_STREAM;
	else if(strncmp(m_channel,"udp",3)==0 || strncmp(m_channel,"UDP",3)==0)
		return SOCK_DGRAM;
	return SOCK_STREAM;
}

const char* CServiceName::GetChannel()const
{
	return m_channel;
}

const char* CServiceName::GetHost()const
{
	return m_host;
}

int CServiceName::GetPort()const
{
	if(strncmp(m_port,"",1) !=0)
		return atoi(m_port);
	else
		return 65563;
}

addr_t CServiceName::GetNHost() const
{
	in_addr addr;
#ifdef WIN32
	addr.s_addr = inet_addr(m_host);
#else
	inet_aton(m_host,&addr);
#endif // WINDOWS

	return addr.s_addr;
}

port_t CServiceName::GetNPort()const
{
	return htons(atoi(m_port));
}

void CServiceName::SetPort(int p)
{
	sprintf(m_port,"%d",p);
}
void CServiceName::SetHost(const char* host)
{
	strncpy(m_host,host,sizeof(m_host));
}
void CServiceName::SetChannel(const char* channel)
{
	strncpy(m_channel,channel,sizeof(m_channel));
}

sockaddr_in CServiceName::GetSock()const
{
	sockaddr_in  addr;
	addr.sin_port =  GetNPort();
	if( GetNChannel() == SOCK_STREAM)
		addr.sin_family = AF_INET;
	else if(GetNChannel() == SOCK_DGRAM)
		addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = GetNHost();
	return addr;
}

void CServiceName::SetSockaddr_in(const sockaddr_in& in)
{
	SetPort(ntohs(in.sin_port));
	if(in.sin_family == AF_INET)
		SetChannel("tcp");
	else
		SetChannel("udp");
	SetHost(inet_ntoa(in.sin_addr));
}

void CServiceName::SetLocation( const char* loc )
{
	strncpy(m_location,loc,sizeof(m_location));
}

const char* CServiceName::GetLocation()
{
	MakeLocation();
	return m_location;
}

void CServiceName::MakeLocation()
{
	sprintf(m_location,"%s://%s:%d/",GetChannel(),GetHost(),GetPort());
}
