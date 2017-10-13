#ifndef LISTENERMANAGER_H
#define LISTENERMANAGER_H

#include "SelectReactor.h"
#include "Handler.h"
#include "Channel.h"
#include <string>
#include "Server.h"

class CListenerManager:public CHandler,public CSelectReactor
{
public:
	CListenerManager(CSelectReactor* outReactor,string listenLocation);

	virtual int HandleEvent(int event,DWORD dwParam,void* pParam); 

	virtual void OnTimer( int event );


	virtual void GetIds( int* readid,int* writeid );

	virtual void HandleInput();

	void SetListenLocation(string connectLocation);

private:


	CChannel* AccpetConnecter();
	void SendAccepted(CChannel* channel);
	CSelectReactor* m_outReactor;
	string m_listenLocation;
	CServer* m_server;
	CChannel* m_serverchannel;

};

#endif