#ifndef CHANNEL_H
#define CHANNEL_H

#include "socks.h"
class CChannel
{

public:
    CChannel(int fd):m_fd(fd){};
    ~CChannel();
   

    int Read(size_t max ,char* buf);
    int Write(size_t max ,char* buf);
    
    int Getfd() const;

private:
    int m_fd;


};
inline int CChannel::Getfd() const
{
    return m_fd;
}

#endif
