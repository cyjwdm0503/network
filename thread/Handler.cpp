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

void CHandler::HandleEvent( int event,DWORD dwParam,void* pParam )
{
	;
}
