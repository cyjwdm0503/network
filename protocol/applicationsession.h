#ifndef APPLICATIONSESSION_H
#define APPLICATIONSESSION_H


#include "contentsession.h"
#include "applicationprotocol.h"
class PackageHandler
{
public:
	virtual int HandlePackage(CPackage* pPackage){return 0;};
};

class CApplicationSession:public CContentSession,public CProtocolCallback,public PackageHandler
{
public:
	CApplicationSession(CDispatcher* dispatcher,CChannel* channel);


	virtual void OnDisconnected( int ErrorCode );


	virtual void OnTimer( int event );

	virtual int HandlePackage(CPackage* pPackage,CProtocol* protocol );

	virtual int HandlePackage(CPackage* pPackage){return 0;};

	CProtocol* GetProtocol();;
private:
	CApplicationProtocol* m_applicationProtocol;
};
#endif