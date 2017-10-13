#include "sessionfactory.h"

void CSessionFactory::OnTimer( int event )
{
	throw std::exception("The method or operation is not implemented.");
}

int CSessionFactory::HandleEvent( int event,DWORD dwParam,void* pParam )
{
	throw std::exception("The method or operation is not implemented.");
}

CSessionFactory::CSessionFactory( CSelectReactor* selectreactor ):CHandler(selectreactor)
{
	m_selectReactor = selectreactor;
	m_connectManager  = new CConnectManager(m_selectReactor,"");
	m_connectManager->SetConnectLocation("tcp://127.0.0.1:1234");

	m_listenManager =  new CListenerManager(m_selectReactor,"");
	m_listenManager->SetListenLocation("tcp://127.0.0.1:2134");
}

