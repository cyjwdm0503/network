/************************************************************************/
/* 
无任何验证的protocol，负责缓存数据。与收发数据。
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
	CChannelProtocol(CSelectReactor* reactor,CChannel* channel,int maxPackageSize);
	virtual ~CChannelProtocol();

	virtual int Push( CPackage* package,CProtocol* protocol );

	virtual void GetIds( int* readid,int* writeid );

	virtual void HandleInput();

	virtual void HandleOupt();

	virtual void OnTimer( int event );


private:
	int m_maxPackageSize;
	CChannel* m_channel;
	CChannelPackage m_channelPackage;
	CCacheList m_cacheList;
};

#endif