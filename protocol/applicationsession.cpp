#include "applicationsession.h"


CApplicationSession::CApplicationSession(CDispatcher* dispatcher,CChannel* channel):
	CContentSession(dispatcher,channel)
{
	m_applicationProtocol = new CApplicationProtocol(dispatcher);
	m_applicationProtocol->AttachLower(m_ContentProtocol);
	m_applicationProtocol->RegisterUpperHandler(this);
}
int CApplicationSession::HandlePackage( CPackage* pPackage,CProtocol* protocol )
{//���������Ӧ��������Ϣ--���߶�Ӧ��������Ϣ
	HandlePackage(pPackage);
	return 0;
}

void CApplicationSession::OnTimer( int event )
{
	CContentSession::OnTimer(event);
}


void CApplicationSession::OnDisconnected( int ErrorCode )
{
	CContentSession::OnDisconnected(ErrorCode);
}

CProtocol* CApplicationSession::GetProtocol()
{
	return m_applicationProtocol;
}


