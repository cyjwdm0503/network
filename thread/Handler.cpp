#include "Handler.h"
#include <cstdlib>

#include "Dispatcher.h"

CHandler::CHandler( CDispatcher* selecter ) :m_dispatcher(selecter)
{
	m_dispatcher->AddHandler(this);
}


CHandler::~CHandler()
{
	if(m_dispatcher != NULL)
		delete m_dispatcher;
	m_dispatcher =  NULL;
}

int CHandler::HandleEvent( int event,DWORD dwParam,void* pParam )
{
	return 0;
}

bool CHandler::PostEvent( int event, DWORD dwParam,void* pParam )
{
	if(m_dispatcher != NULL)
		return m_dispatcher->PostEvent(this,event,dwParam,pParam);
	return false;
}

void CHandler::SetTimer( int event,int elapse )
{
	if(m_dispatcher != NULL)
		m_dispatcher->RegisterTimer(this,event,elapse);
}

int CHandler::SendEvent( int event, DWORD dwParam, void* pParam )
{
	if(m_dispatcher != NULL)
		return 	m_dispatcher->SendEvent(this,event,dwParam, pParam);
	return 0;
}

void CHandler::KillTimer( int event )
{
	if(m_dispatcher != NULL)
		m_dispatcher->RemoveTimer(this,event);
}
