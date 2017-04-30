/************************************************************************/
/* 
*/
/************************************************************************/
#ifndef CONTENTSESSION_H
#define CONTENTSESSION_H
#include "session.h"
#include "contentprotocol.h"

class CChannelSession:public CSession
{
public:
	CChannelSession(CDispatcher *selecter,CChannel *pChannel,int MaxPackageSize):CSession(selecter,pChannel,MaxPackageSize){};
	virtual ~CChannelSession(){};

	void GetIds( int* readid,int* writeid ){CSession::GetIds(readid,writeid);};


	 void HandleInput(){CSession::HandleInput();};

	 void HandleOupt(){CSession::HandleOupt();};

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

#endif