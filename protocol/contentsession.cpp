#include "contentsession.h"
#include "contentpackage.h"
#include "Log.h"


CContentSession::CContentSession( CDispatcher *selecter,CChannel *pChannel):
	CChannelSession(selecter,pChannel,MAX_CONTENT_PACKAGE_LEN+CONTENTHEADLENGTH+CONTENTEXTHEADLENGTH+MAX_CONTENT_LEN)
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
