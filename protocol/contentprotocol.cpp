#include "contentprotocol.h"
#include "contentpackage.h"
#include <ctime>
#include "Log.h"

#define  CONTENTPROTOCOL_CHECKTIME_ID	11


int CContentProtocol::Pop( CPackage* package )
{
	
	CContentPackage* contentpackage = dynamic_cast<CContentPackage*>(package);
	if(contentpackage == NULL)
		return -1;
	if(contentpackage->GetActiveID() == CONTENTTYPENANO)
	{//��ǰЭ��ı���
		if(contentpackage->GetExtTag() == CONTENT_HEART_TIMEOUT)
		{
			set_timeout(package);
			CLog::GetInstance()->PrintLog("Recevie Server TimeOut Set Package\n");
			return 0;
		}
		
		if(contentpackage->GetExtTag() == CONTENT_HEART_TAG)
		{
			m_LastReadTime = m_dispatcher->Time();
			CLog::GetInstance()->PrintLog("Receive Heartbeat, CurrentTime=%d\n",m_dispatcher->Time());
			return 0;
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
	//m_LastReadTime = m_dispatcher->Time();
	//�����push�趨activeIDҲ������ͳһ�Ľӿ�ʵ�ֵġ�
	((CContentPackage*)m_sendPackage)->GetContentHeader()->Type =  protocol->GetActiveID();
	return CProtocol::Push(package,protocol);
}

void CContentProtocol::OnTimer( int event )
{
	/***���ڼ���ӦЭ���µ�����ʱ��,..�������timeout�����ⷢ��������*/
	if(event == CONTENTPROTOCOL_CHECKTIME_ID)
	{
		if(m_dispatcher->Time() - m_LastReadTime >= 3*m_timeOut)
		{//���ϴζ�����ʱ��̫Զ�ˣ����ܷ������Ѿ��ҵ�
			NotifyErr(EVENT_CONTENT_READTIMEOUT,0,this);
		}

		if(m_dispatcher->Time() -  m_LastWriteTime >= m_timeOut)
		{//���ϴζ���д���ݵ�ʱ���Ѿ���Զ�ˡ���������	
			if( !SendHeartTag())
				NotifyErr(EVENT_CONTENT_WRITETIMEOUT,0,this);
		}

		
	}
	CProtocol::OnTimer(event);
}

CContentProtocol::CContentProtocol( CDispatcher* reactor ):CProtocol(reactor,new CContentPackage(),new CContentPackage(),CONTENTHEADLENGTH+CONTENTEXTHEADLENGTH)
{
	m_timeOut = 9999999;
	m_LastReadTime = reactor->Time();
	m_LastWriteTime = reactor->Time();
	
}

CContentProtocol::~CContentProtocol()
{

}

void CContentProtocol::send_timeout( int timeout )
{
	CContentPackage sendpackage;
	sendpackage.ConstructAlloc(0,GetReserverLen());
	sendpackage.SetExtHeader(CONTENT_HEART_TIMEOUT,sizeof(int),(char*)&timeout);
	send(&sendpackage);
}

void CContentProtocol::set_timeout( CPackage* package )
{//�����յ���ʱ�䳬ʱ���ģ��趨���������ĳ�ʱʱ��
	CContentPackage* contentpkg = dynamic_cast<CContentPackage*>(package);
	if(contentpkg == NULL)
		return;
	if(contentpkg->GetExtTag() != CONTENT_HEART_TIMEOUT)
		return ;
	if(contentpkg->GetExtTagLen() != sizeof(m_timeOut))
		return;
	memcpy(&m_timeOut,contentpkg->GetExtData(),sizeof(m_timeOut));
}

void CContentProtocol::set_timecheck( bool flag )
{
	if(flag)
	{
		SetTimer(CONTENTPROTOCOL_CHECKTIME_ID,2000);
		send_timeout(20);
	}
	else
	{
		KillTimer(CONTENTPROTOCOL_CHECKTIME_ID);
	}
	
}

bool CContentProtocol::SendHeartTag()
{
	CContentPackage heartpackage;
	int len =  GetReserverLen();
	heartpackage.ConstructAlloc(0,len);
	heartpackage.SetExtHeader(CONTENT_HEART_TAG,0,NULL);
	m_LastWriteTime =  m_dispatcher->Time();
	int ret = send(&heartpackage);
	if(ret < 0)
		return false;
	return true;
}

