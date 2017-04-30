#include "contentprotocol.h"
#include "contentpackage.h"
#include <ctime>
#include "Log.h"

#define  CONTENTPROTOCOL_CHECKTIME_ID	1
const EVENT_MSG EVENT_MSG_READTIMEOUT = 201;
const EVENT_MSG EVENT_MSG_WRITETIMEOUT = 301;

int CContentProtocol::Pop( CPackage* package )
{
	m_LastReadTime = m_dispatcher->Time();
	CContentPackage* contentpackage = dynamic_cast<CContentPackage*>(package);
	if(contentpackage == NULL)
		return -1;
	if(contentpackage->GetActiveID() == CONTENTTYPENANO)
	{//��ǰЭ��ı���
		if(contentpackage->GetExtTag() == CONTENT_HEART_TIMEOUT)
		{
			set_timeout(package);
			return 0;
		}
		
		if(contentpackage->GetExtTag() == CONTENT_HEART_TAG)
		{
			char info[1024];
			sprintf(info," Receive Heartbeat, CurrentTime=%d\n",m_dispatcher->Time());
			CLog::GetInstance()->PrintLog(info);
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
	m_LastReadTime = m_dispatcher->Time();
	((CContentPackage*)m_sendPackage)->GetContentHeader()->Type =  protocol->GetActiveID();
	return CProtocol::Push(package,protocol);
}

void CContentProtocol::OnTimer( int event )
{
	/***���ڼ���ӦЭ���µ�����ʱ��,..�������timeout�����ⷢ��������*/
	if(event == CONTENTPROTOCOL_CHECKTIME_ID)
	{
		if(m_dispatcher->Time() - m_LastReadTime >= 2*m_timeOut)
		{//���ϴζ�����ʱ��̫Զ�ˣ����ܷ������Ѿ��ҵ�
			NotifyErr(EVENT_MSG_READTIMEOUT,0,this);
		}

		if(m_dispatcher->Time() -  m_LastWriteTime >= m_timeOut)
		{//���ϴζ���д���ݵ�ʱ���Ѿ���Զ�ˡ���������
		
			if( !SendHeartTag())
				NotifyErr(EVENT_MSG_WRITETIMEOUT,0,this);
		}

		
	}
	CProtocol::OnTimer(event);
}

CContentProtocol::CContentProtocol( CDispatcher* reactor ):CProtocol(reactor,new CContentPackage(),new CContentPackage(),CONTENTHEADLENGTH+CONTENTEXTHEADLENGTH+MAX_CONTENT_LEN)
{
	m_timeOut = 0;
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
{
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
	if(m_needchecktime)
	{
		SetTimer(CONTENTPROTOCOL_CHECKTIME_ID,2000);
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

