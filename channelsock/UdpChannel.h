/*
*/
#ifndef UDPCHANNEL_H
#define UDPCHANNEL_H
#include "Channel.h"
class CUdpChannel:public CChannel
{
public:
	CUdpChannel(int fd);
	virtual int Read(size_t max ,char* buf);
	virtual int Write(size_t max ,const char* buf);
 
};

#endif