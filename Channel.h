/**
用于将一组 对外提供对读写的操作接口

**/
#ifndef CHANNEL_H
#define CHANNEL_H
#include "socks.h"
#include "ServiceName.h"
class CChannel
{

public:
    CChannel(int fd):m_fd(fd){};
    ~CChannel();


    int Read(size_t max ,char* buf);
    int Write(size_t max ,char* buf);
    CServiceName* GetService(){return m_service;};
    void SetService(const CServiceName& service);
    //获取此的对应文件描述符的id
    int Getfd() const;

private:
    int m_fd;
    CServiceName* m_service;


};



#endif
