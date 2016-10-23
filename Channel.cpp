#include "Channel.h"



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
    read(m_fd,buf,max);
    return 0;
}

int CChannel::Write(size_t max,char* buf)
{
    write(m_fd,buf,max);
    return 0;
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
