#ifndef SERVICE_H
#define SERVICE_H
#include "socks.h"
#include "Log.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
typedef int addr_t;
typedef unsigned short port_t;
typedef int channel_t;

class CServiceName
{
   // typedef int addr_t;
   // typedef unsigned short port_t;
public:
    CServiceName(const char* location);
    char* GetChannel();
    char* GetHost();
    int GetPort();
    channel_t GetNChannel();
    port_t GetNPort();
    addr_t GetNHost();
    void SetPort(int);
    void SetHost(const char*);
    void SetChannel(const char*);
private:
    char m_host[128];
    char m_port[64];
    char m_location[256];
    char m_channel[64];

};
#endif
