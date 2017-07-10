#ifndef APPLICATIONSESSION_H
#define APPLICATIONSESSION_H


#include "contentsession.h"
class CApplicationSession:public CContentSession,public CProtocolCallback
{
public:
	CApplicationSession(CDispatcher* selecter,CChannel* channel);
	~CApplicationSession();
	virtual int HandleEvent( int event,DWORD dwParam,void* pParam );

	virtual void OnDisconnected( int ErrorCode );

	virtual void Disconected( int event );

	virtual void OnTimer( int event );

	virtual int HandlePackage( CPackage* pPackage,CProtocol* protocol );
private:
		
};
#endif