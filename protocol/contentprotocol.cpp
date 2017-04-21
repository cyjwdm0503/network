#include "contentprotocol.h"
#include "contentpackage.h"

int CContentProtocol::Pop( CPackage* package )
{
	CContentPackage* contentpackage = dynamic_cast<CContentPackage*>(package);
	if(contentpackage == NULL)
		return -1;
	if(contentpackage->GetActiveID() == CONTENTTYPENANO)
	{//��ǰЭ��ı���
		if(contentpackage->GetExtTag() == CONTENT_HEART_TAG)
		{
			set_timeout(package);
		}
		else if(contentpackage->GetExtTag() == CONTENT_ANSWER_TAG)
		{
			;
		}
	}
	
	//������Ǹò�ı��ģ������Ͻ���Pop
	return CProtocol::Pop(package);
}

int CContentProtocol::OnRecvErrPackage( CPackage* package )
{
	return CProtocol::OnRecvErrPackage(package);
}

int CContentProtocol::Push( CPackage* package,CProtocol* protocol )
{
	((CContentPackage*)m_sendPackage)->GetContentHeader()->Type =  package->GetActiveID();
	return CProtocol::Push(package,protocol);
}

void CContentProtocol::OnTimer( int event )
{
	CProtocol::OnTimer(event);
}

CContentProtocol::CContentProtocol( CSelectReactor* reactor ):CProtocol(reactor,new CContentPackage(),new CContentPackage(),CONTENTHEADLENGTH+CONTENTEXTHEADLENGTH+MAX_CONTENT_LEN)
{
	m_timeOut = 0;
}

CContentProtocol::~CContentProtocol()
{

}

void CContentProtocol::send_timeout( int timeout )
{
	CContentPackage sendpackage;
	sendpackage.ConstructAlloc(0,GetReserverLen());
	sendpackage.SetExtHeader(CONTENT_HEART_TAG,sizeof(int),(char*)&timeout);
	send(&sendpackage);
}

void CContentProtocol::set_timeout( CPackage* package )
{
	CContentPackage* contentpkg = dynamic_cast<CContentPackage*>(package);
	if(contentpkg == NULL)
		return;
	if(contentpkg->GetExtTag() != CONTENT_HEART_TAG)
		return ;
	if(contentpkg->GetExtTagLen() != sizeof(m_timeOut))
		return;
	memcpy(&m_timeOut,contentpkg->GetExtData(),sizeof(m_timeOut));
}

void CContentProtocol::set_timecheck( bool flag )
{
	m_checktime =  flag;
}

