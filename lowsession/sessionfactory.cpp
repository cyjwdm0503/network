#include "sessionfactory.h"
#include "Log.h"
#include <exception>
void CSessionFactory::OnTimer( int event )
{
    throw std::exception();
}

int CSessionFactory::HandleEvent( int event,DWORD dwParam,void* pParam )
{
	switch(event)
	{
	case EVENT_CONNECT_SUCCESS:
		CreateSession((CChannel*)pParam);
		break;
	case EVENT_ACCEPT_SUCCESS:
		CreateSession((CChannel*)pParam);
	default:
		break;
	}
	return 0;
}

CSessionFactory::CSessionFactory( CSelectReactor* selectreactor ):CHandler(selectreactor)
{
	m_selectReactor = selectreactor;
	m_connectManager  = NULL;
	m_listenManager = NULL;
}

void CSessionFactory::OnConnected( int code )
{
	if(m_connectManager != NULL)
	{
		m_connectManager->PostEvent(EVENT_CONNECT_SUCCESS,0,NULL);
	}
	if(m_listenManager != NULL)
	{
		m_listenManager->PostEvent(EVENT_ACCEPT_SUCCESS,0,NULL);
	}
}

void CSessionFactory::OnDisConnected( int code )
{
	if(m_connectManager != NULL)
	{
		m_connectManager->PostEvent(EVENT_CONNECT_FAILED,0,NULL);
	}
	if(m_listenManager != NULL)
	{
		m_listenManager->PostEvent(EVENT_ACCEPT_FAILED,0,NULL);
	}
}

void CSessionFactory::SetConnectLoc( string connectLoc )
{
	m_connectManager = new CConnectManager(m_selectReactor,"");
	m_connectManager->SetConnectLocation(connectLoc);
}

void CSessionFactory::SetListenLoc( string listenLoc )
{
	m_listenManager = new CListenerManager(m_selectReactor,"");
	m_listenManager->SetListenLocation(listenLoc);
}

void CSessionFactory::Start()
{
	if(m_connectManager != NULL)
	{
		m_connectManager->Create();
		m_connectManager->Join();
	}
	if(m_listenManager != NULL)
	{
		m_listenManager->Create();
		m_listenManager->Join();
	}
}

CSession* CSessionFactory::CreateSession( CChannel* channel )
{
	//CSession* session = new CSession(m_selectReactor,channel,4096);
	//m_selectReactor->AddHandler(session);
	//session->RegisterConnectCallback(this);
	//return session;

	CLog::GetInstance()->PrintLog("CreateSession");
	return NULL;

}

