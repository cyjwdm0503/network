#include "Channel.h"



CChannel::~CChannel()
{

}

int CChannel::Read(size_t max,char* buf)
{
    read(m_fd,buf,max);
    return 0;
}

int CChannel::Write(size_t max,char* buf)
{
    write(m_fd,buf,max);
    return 0;
}

