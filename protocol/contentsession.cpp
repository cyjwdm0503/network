#include "contentsession.h"

#include "Log.h"




CContentSession::CContentSession( CDispatcher *selecter,CChannel *pChannel):
	CChannelSession(selecter,pChannel,MAX_CONTENT_PACKAGE_LEN+CONTENTHEADLENGTH+CONTENTEXTHEADLENGTH)
{
	m_ContentProtocol = new CContentProtocol(selecter);
	m_ContentProtocol->AttachLower(m_ChannelProtocol);
	m_ContentProtocol->RegisterErrHandler(this);
	//m_ContentProtocol->set_timecheck(true);
}

CContentSession::~CContentSession()
{
	delete m_ContentProtocol;
	m_ContentProtocol = NULL;

}

 

int CContentSession::HandleEvent( int event,DWORD dwParam,void* pParam )
{	
	switch (event)
	{
	case EVENT_CONTENT_READTIMEOUT:
		OnReadError(event);
	case EVENT_CONTENT_WRITETIMEOUT:
		OnWriteError(event);
		OnDisconnected(event);
	default:
		break;
	}
	return CChannelSession::HandleEvent(event,dwParam,pParam);
}

void CContentSession::OnDisconnected( int ErrorCode )
{
	 m_ContentProtocol->set_timecheck(false);
	 CChannelSession::OnDisconnected(ErrorCode);

}

