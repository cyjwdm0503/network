/************************************************************************/
/* 
*/
/************************************************************************/
#ifndef CONTENTSESSION_H
#define CONTENTSESSION_H
#include "session.h"
#include "contentprotocol.h"
#include "contentpackage.h"
#include "channelsession.h"


class CContentSession:public CChannelSession
{
public:
	CContentSession(CDispatcher *selecter,CChannel *pChannel);
	virtual ~CContentSession();

	virtual int HandleEvent( int event,DWORD dwParam,void* pParam );

	virtual void OnDisconnected( int ErrorCode );

protected:
	CContentProtocol* m_ContentProtocol;

};

#ifdef SESSION_DEBUG
const EVENT_MSG SESSION_MSG = 0xFFFFFFFF;
const unsigned char SESSION_EXTTAG = 0xFF;
class CClientContent:public CContentSession,public CProtocolCallback
{
public:
	CClientContent(CDispatcher* selecter,CChannel* channel);

	//�յ����ݽ���չʾ
	virtual int HandlePackage( CPackage* pPackage,CProtocol* protocol );

	//��ʱ��ײ㷢������
	virtual void OnTimer( int event );

	virtual void OnDisconnected( int ErrorCode );
private:
	int m_id;
	CContentPackage package;
};
#endif

#endif