#include "ServiceName.h"
#include <cstring>
using namespace std;

CServiceName::CServiceName(const char* location):m_host(),m_port(),m_location(),m_channel()
{
   strcpy(m_location,location);
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
           && bhost == false)
        {
            endpos =  pos;
            if(beginpos !=0)
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
           && (m_location[pos] == '\0'
               || m_location[pos] == '/'))
         {
             strncpy(m_port,m_location+beginpos,endpos-beginpos);
             bport = true;
             m_port[endpos-beginpos]= '\0';
         }
        pos++;
   }
}

 channel_t CServiceName::GetNChannel()
{
   if(strncmp(m_channel,"tcp",3)==0 || strncmp(m_channel,"TCP",3)==0)
       return SOCK_STREAM;
   else if(strncmp(m_channel,"udp",3)==0 || strncmp(m_channel,"UDP",3)==0)
       return SOCK_DGRAM;
    return SOCK_STREAM;
}

 char* CServiceName::GetChannel()
{
    return m_channel;
}

 char* CServiceName::GetHost()
{
    return m_host;
}

 int CServiceName::GetPort()
{
  if(strncmp(m_port,"",1) !=0)
    return atoi(m_port);
  else
    return 65563;
}

  addr_t CServiceName::GetNHost()
{
    in_addr addr;
    inet_aton(m_host,&addr);
    return addr.s_addr;
}

  port_t CServiceName::GetNPort()
{
    return htons(atoi(m_port));
}

  void CServiceName::SetPort(int p)
{
  sprintf(m_port,"%d",p);
}
  void CServiceName::SetHost(const char* host)
{
  strncpy(m_host,host,strlen(m_host));
}
  void CServiceName::SetChannel(const char* channel)
{
  strncpy(m_channel,channel,strlen(m_channel));
}

sockaddr_in CServiceName::GetSock()
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
