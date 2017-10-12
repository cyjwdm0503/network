#include "sessionfactory.h"

void CSessionFactory::OnTimer( int event )
{
	throw std::exception("The method or operation is not implemented.");
}

int CSessionFactory::HandleEvent( int event,DWORD dwParam,void* pParam )
{
	throw std::exception("The method or operation is not implemented.");
}

CSessionFactory::CSessionFactory( CSelectReactor* selectreactor )
{
	m_selectReactor = selectreactor;
	m_connectManager  = new CConnectManager(m_selectReactor);
	m_listenManager =  new CListenerManager(m_selectReactor);
}

