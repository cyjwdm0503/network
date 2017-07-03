#include "session.h"
#include <ctime>

unsigned int SESSION_ID = 0;
CSession::CSession(CDispatcher *pReactor,CChannel *pChannel,int MaxPackageSize ):CHandler(pReactor),m_Channel(pChannel)
{
	m_ChannelProtocol =  new CChannelProtocol(pReactor,m_Channel,MaxPackageSize);
	m_ChannelProtocol->RegisterErrHandler(this);
	m_SessionCallback = NULL;
	m_SessionID = ++SESSION_ID + time(NULL)<<16;
}

CSession::~CSession()
{
	delete m_ChannelProtocol;
	m_ChannelProtocol = NULL;
	
	m_Channel->Disconnect();
	delete m_Channel;
	m_Channel = NULL;

}

void CSession::GetIds( int* readid,int* writeid )
{
	m_ChannelProtocol->GetIds(readid,writeid);
}


int CSession::HandleEvent( int event,DWORD dwParam,void* pParam )
{
	switch (event)
	{
	case EVENT_CHANNEL_WRITE_ERRO:
	case EVENT_CHANNEL_READ_ERRO:
		Disconected(event);
	default:
		break;
	}
	return 0;
}

void CSession::HandleInput()
{
	m_ChannelProtocol->HandleInput();
}

void CSession::HandleOutput()
{
	
	m_ChannelProtocol->HandleOutput();
}

void CSession::Disconected( int event )
{
	if(m_SessionCallback != NULL)
	{
		m_SessionCallback->OnDisconnected(event);
	}
}

void CSession::RegisterSessionCallback( CSessionCallback* callback )
{
	m_SessionCallback = callback;
}
