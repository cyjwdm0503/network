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
