#ifndef SERVICE_H
#define SERVICE_H
#include "socks.h"
#include <cstdlib>
#include <cstring>
typedef int addr_t;
typedef unsigned short port_t;
typedef int channel_t;

class CServiceName
{
   // typedef int addr_t;
   // typedef unsigned short port_t;
public:
    CServiceName(const char* location);
    inline char* GetChannel();
    inline char* GetHost();
    inline int GetPort();
    inline channel_t GetNChannel();
    inline port_t GetNPort();
    inline addr_t GetNHost();
    inline void SetPort(int);
    inline void SetHost(const char*);
    inline void SetChannel(const char*);
private:
    char m_host[128];
    char m_port[64];
    char m_location[256];
    char m_channel[64];

};

inline channel_t CServiceName::GetNChannel()
{
   if(strncmp(m_channel,"tcp",3)==0 || strncmp(m_channel,"TCP",3)==0)
       return SOCK_STREAM;
   else if(strncmp(m_channel,"udp",3)==0 || strncmp(m_channel,"UDP",3)==0)
       return SOCK_DGRAM;

}

inline char* CServiceName::GetChannel()
{
    return m_channel;
}

inline char* CServiceName::GetHost()
{

    return m_host;
}

inline int CServiceName::GetPort()
{
  if(strncmp(m_port,"",1) !=0)
    return atoi(m_port);
  else
    return 65563;
}

inline addr_t CServiceName::GetNHost()
{
    in_addr addr;
    inet_aton(m_host,&addr);
    return addr.s_addr;
}

inline port_t CServiceName::GetNPort()
{
    return htons(atoi(m_port));
}

inline void CServiceName::SetPort(int p)
{
  sprintf(m_port,"%d",p);
}
inline void CServiceName::SetHost(const char* host)
{
  strncpy(m_host,host,strlen(m_host));
}
inline void CServiceName::SetChannel(const char* channel)
{
  strncpy(m_channel,channel,strlen(m_channel));
}
#endif
