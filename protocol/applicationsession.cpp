#include "applicationsession.h"

CApplicationSession::CApplicationSession( CDispatcher* selecter,CChannel* channel):CContentSession(selecter,channel)
{
	
}

CApplicationSession::~CApplicationSession()
{

}

int CApplicationSession::HandlePackage( CPackage* pPackage,CProtocol* protocol )
{//���������Ӧ��������Ϣ
	return 0;
}

void CApplicationSession::OnTimer( int event )
{
	throw std::exception("The method or operation is not implemented.");
}

void CApplicationSession::Disconected( int event )
{
	CContentSession::Disconected(event);
}

void CApplicationSession::OnDisconnected( int ErrorCode )
{
	throw std::exception("The method or operation is not implemented.");
}

int CApplicationSession::HandleEvent( int event,DWORD dwParam,void* pParam )
{
	throw std::exception("The method or operation is not implemented.");
}



