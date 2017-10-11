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
    CChannel(int fd);
    virtual ~CChannel();


    virtual int Read(size_t max ,char* buf);
    virtual int Write(size_t max ,const char* buf);
    virtual CServiceName* GetService();
    virtual void SetService(const CServiceName& service);
    //获取此的对应文件描述符的id
    int Getfd() const;
	bool Available();
	bool Disconnect();

protected:
    int m_fd;
    CServiceName* m_service;
	bool m_bConnected;


};



#endif
