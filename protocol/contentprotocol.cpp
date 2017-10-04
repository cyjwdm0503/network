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
	{//当前协议的报文
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
	
	//如果不是该层的报文，则线上进行Pop
	return CProtocol::Pop(package);
}

int CContentProtocol::OnRecvErrPackage( CPackage* package )
{
	return CProtocol::OnRecvErrPackage(package);
}

int CContentProtocol::Push( CPackage* package,CProtocol* protocol )
{
	//m_LastReadTime = m_dispatcher->Time();
	//这里的push设定activeID也可以用统一的接口实现的。
	((CContentPackage*)m_sendPackage)->GetContentHeader()->Type =  protocol->GetActiveID();
	return CProtocol::Push(package,protocol);
}

void CContentProtocol::OnTimer( int event )
{
	/***用于检查对应协议下的心跳时间,..如果超过timeout。向外发送心跳包*/
	if(event == CONTENTPROTOCOL_CHECKTIME_ID)
	{
		if(m_dispatcher->Time() - m_LastReadTime >= 3*m_timeOut)
		{//离上次读到的时间太远了，可能服务器已经挂掉
			NotifyErr(EVENT_CONTENT_READTIMEOUT,0,this);
		}

		if(m_dispatcher->Time() -  m_LastWriteTime >= m_timeOut)
		{//离上次对外写数据的时间已经很远了。发送心跳	
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
{//根据收到的时间超时报文，设定发送心跳的超时时间
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

