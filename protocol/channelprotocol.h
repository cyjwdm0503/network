/************************************************************************/
/* 
无任何验证的protocol，负责缓存数据。与收发数据。
后续需要处理写入和读取失败的逻辑，然后不再对改套接字的session进行调度--通过修改SessionCallBack完成
*/
/************************************************************************/
#ifndef CHANNELPROTOCOL_H
#define CHANNELPROTOCOL_H
#include "channelpackage.h"
#include "Protocol.h"
#include "cachelist.h"

class CChannelProtocol:public CProtocol
{
public:
	CChannelProtocol(CDispatcher* reactor,CChannel* channel,int maxPackageSize);
	virtual ~CChannelProtocol();

	virtual int Push( CPackage* package,CProtocol* protocol );

	virtual void GetIds( int* readid,int* writeid );

	virtual void HandleInput();

	virtual void HandleOutput();

	virtual void OnTimer( int event );


private:
	int m_maxPackageSize;
	CChannel* m_channel;
	CChannelPackage m_channelPackage;
	CCacheList* m_cacheList;
};

#endif