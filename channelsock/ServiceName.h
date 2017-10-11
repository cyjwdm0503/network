#ifndef SERVICE_H
#define SERVICE_H
#include "socks.h"

typedef int addr_t;
typedef unsigned short port_t;
typedef int channel_t;

class CServiceName
{
   // typedef int addr_t;
   // typedef unsigned short port_t;
public:
	CServiceName();
	CServiceName(const char* location);
	CServiceName(const CServiceName& ser);
	const char* GetChannel() const;
	const char* GetHost() const;
	int GetPort() const;
	const char* GetLocation();
	void SetLocation(const char* loc);
	channel_t GetNChannel() const;
	port_t GetNPort() const;
	addr_t GetNHost() const;
	void SetPort(int);
	void SetHost(const char*);
	void SetChannel(const char*);
	sockaddr_in GetSock() const;
	void SetSockaddr_in(const sockaddr_in& in);

private:
	void MakeLocation();
	char m_host[128];
	char m_port[64];
	char m_location[256];
	char m_channel[64];
	

};


#endif
