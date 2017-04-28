/************************************************************************/
/* 用于处理channelprotocol层的消息发送以及错误消息处理的session
因为session也是被事件调度的类，因此要继承与CHandler
因为以后对外提供的都是session的输入输出接口，因此要将channel进行封装

为方便提供自定义的回调处理。提供一个回调参数
*/
/************************************************************************/
#ifndef CHAANELSESSION_H
#define CHANNELSESSION_H

#include "channelprotocol.h"
#include "Handler.h"

class CSessionCallback
{
public:
	virtual void OnReadError(int ErrorCode){};
	virtual void OnWriteError(int ErrorCode){};
	virtual void OnDisconnected(int ErrorCode){};
	virtual void OnConnected(int Code){};
};

class CSession:public CHandler
{
public:
	CSession(CDispatcher *selecter,CChannel *pChannel,int MaxPackageSize);
	~CSession();

	virtual void GetIds( int* readid,int* writeid );


	virtual int HandleEvent( int event,DWORD dwParam,void* pParam );

	virtual void HandleInput();

	virtual void HandleOupt();

	virtual void Disconected( int event );
protected:
	CChannelProtocol* m_ChannelProtocol;
	CChannel* m_Channel;
	CSessionCallback* m_SessionCallback;
	unsigned int m_SessionID;

};




#endif