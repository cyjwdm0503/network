/************************************************************************/
/* 
*/
/************************************************************************/
#ifndef CONTENTSESSION_H
#define CONTENTSESSION_H
#include "session.h"
#include "contentprotocol.h"

class CChannelSession:public CSession,public CSessionCallback
{
public:
	CChannelSession(CDispatcher *selecter,CChannel *pChannel,int MaxPackageSize):CSession(selecter,pChannel,MaxPackageSize){};
	virtual ~CChannelSession(){};

	void GetIds( int* readid,int* writeid ){CSession::GetIds(readid,writeid);};


	void HandleInput(){CSession::HandleInput();};

	void HandleOupt(){CSession::HandleOupt();};

	virtual void OnDisconnected( int ErrorCode );

private:

};

class CContentSession:public CChannelSession,public CProtocolCallback
{
public:
	CContentSession(CDispatcher *selecter,CChannel *pChannel);
	virtual ~CContentSession();

	virtual int HandlePackage( CPackage* pPackage,CProtocol* protocol );
protected:
	CContentProtocol* m_ContentProtocol;

};

#ifdef SESSION_DEBUG
const EVENT_MSG SESSION_MSG = 0xFFFFFFFF;
const unsigned char SESSION_EXTTAG = 0xFF;
class CClientContent:public CContentSession
{
public:
	CClientContent(CDispatcher* selecter,CChannel* channel);

	//收到数据进行展示
	virtual int HandlePackage( CPackage* pPackage,CProtocol* protocol );

	//定时向底层发送数据
	virtual void OnTimer( int event );
private:
	int m_id;

};
#endif

#endif