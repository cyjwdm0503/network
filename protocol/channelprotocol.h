/************************************************************************/
/* 
���κ���֤��protocol�����𻺴����ݡ����շ����ݡ�
������Ҫ����д��Ͷ�ȡʧ�ܵ��߼���Ȼ���ٶԸ��׽��ֵ�session���е���--ͨ���޸�SessionCallBack���
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