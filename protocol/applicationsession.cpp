#include "applicationsession.h"

int CApplicationSession::HandlePackage( CPackage* pPackage,CProtocol* protocol )
{//���������Ӧ��������Ϣ

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

