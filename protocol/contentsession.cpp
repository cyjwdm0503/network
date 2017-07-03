#include "contentsession.h"
#include "contentpackage.h"
#include "Log.h"


CContentSession::CContentSession( CDispatcher *selecter,CChannel *pChannel):
	CChannelSession(selecter,pChannel,MAX_CONTENT_PACKAGE_LEN+CONTENTHEADLENGTH+CONTENTEXTHEADLENGTH)
{
	m_ContentProtocol = new CContentProtocol(selecter);
	m_ContentProtocol->AttachLower(m_ChannelProtocol);
	m_ContentProtocol->RegisterErrHandler(this);
	m_ContentProtocol->RegisterUpperHandler(this);
	m_ContentProtocol->set_timecheck(false);
}

CContentSession::~CContentSession()
{
	delete m_ContentProtocol;
	m_ContentProtocol = NULL;

}

int CContentSession::HandlePackage( CPackage* pPackage,CProtocol* protocol )
{
	try
	{
		CContentPackage* content = dynamic_cast<CContentPackage*>(pPackage);
		int i=0;
		if(content != NULL)
		{
			 
#ifdef CLIENT
			cout<<content->Length()<<"\t"<<content->GetContentHeader()->Type<<endl;
#endif
		}
	}
	catch(exception &e)
	{
		CLog::GetInstance()->PrintLog(e.what());
	}
	return 0;

}

#ifdef  SESSION_DEBUG

CClientContent::CClientContent( CDispatcher* selecter,CChannel* channel ):CContentSession(selecter,channel)
{	
	SetTimer(SESSION_MSG,10);
	m_id = 0;
}

int CClientContent::HandlePackage( CPackage* pPackage,CProtocol* protocol )
{
	try
	{
		CContentPackage* content = dynamic_cast<CContentPackage*>(pPackage);
		int i=0;
		if(content != NULL)
		{
			if(content->GetExtTag() == SESSION_EXTTAG)
			{
				cout<<content->Length()<<"\t"<<content->GetContentHeader()->Type<<endl;
				cout<<content->GetExtTag()<<"\t"<<content->GetExtData()<<endl;
			}
			
		}
	}
	catch(exception &e)
	{
		CLog::GetInstance()->PrintLog(e.what());
	}
	return 0;
}

void CClientContent::OnTimer( int event )
{
	if(event == SESSION_MSG)
	{
		CContentPackage package;
		package.ConstructAlloc(0,CONTENTHEADLENGTH+CONTENTEXTHEADLENGTH);
		char buf[64] ;
#ifdef SERVER
		sprintf(buf,"SERVER:%d",++m_id);
		package.SetExtHeader(SESSION_EXTTAG,strlen(buf)+1,buf);
#else
		sprintf(buf,"CLIENT:%d",++m_id);
		package.SetExtHeader(SESSION_EXTTAG,strlen(buf)+1,buf);
#endif
		CLog::GetInstance()->PrintLog("%s\n",buf);
		m_ContentProtocol->send(&package);
	}
	CContentSession::OnTimer(event);
}

#endif