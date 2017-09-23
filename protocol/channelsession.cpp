#include "channelsession.h"


void CChannelSession::HandleOutput()
{
	CSession::HandleOutput();
}

void CChannelSession::HandleInput()
{
	CSession::HandleInput();
}

void CChannelSession::GetIds( int* readid,int* writeid )
{
	CSession::GetIds(readid,writeid);
}

CChannelSession::~CChannelSession()
{

}

CChannelSession::CChannelSession( CDispatcher *selecter,CChannel *pChannel,int MaxPackageSize ) :CSession(selecter,pChannel,MaxPackageSize)
{
	m_ChannelProtocol->RegisterErrHandler(this);
}

void CChannelSession::OnDisconnected( int ErrorCode )
{
	if(ErrorCode != EVENT_CHANNEL_READ_ERRO && ErrorCode != EVENT_CHANNEL_WRITE_ERRO)
	{
		m_ChannelProtocol->HandleOutput();
	}
	m_Channel->Disconnect();
	CSessionCallback::OnDisconnected(ErrorCode);
}

int CChannelSession::HandleEvent( int event,DWORD dwParam,void* pParam )
{
	switch (event)
	{
	case EVENT_CHANNEL_WRITE_ERRO:
		OnWriteError(event);
		OnDisconnected(event);
		break;
	case EVENT_CHANNEL_READ_ERRO:
		OnReadError(event);
		OnDisconnected(event);
		break;
	default:
		break;
	}
	return 0;
}