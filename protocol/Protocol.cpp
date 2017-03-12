#include "Protocol.h"

CProtocol::CProtocol( CSelectReactor* reactor,CPackage* pUpperPackage,CPackage* pSendPackage,int ReserverLen ):CHandler(reactor)
{
	m_activeid=0;
	m_pErrHandler = NULL;
	m_pUppderHandler = NULL;
	m_reservelen = ReserverLen;
	m_sendPackage = pSendPackage;
	m_upperPackage =  pUpperPackage;
	p_lower = NULL;

}

CProtocol::~CProtocol()
{
	if(GetLower() != NULL)
	{
		((CProtocol*)GetLower())->RemoveUpper(GetActiveID());
	}
	if(m_UpperMap.size() >0)
	{
		m_UpperMap.clear();
	}
	if(m_upperPackage != NULL)
	{
		m_upperPackage->Release();
	}
	if(m_sendPackage != NULL)
		m_sendPackage->Release();

}

void CProtocol::AttachLower( CProtocol* pLower)
{
	if(pLower != NULL)
	{
		pLower->AddUpper(this);
	}
	p_lower = pLower;

}

void CProtocol::RegisterUpperHandler( CProtocolCallback* pUpperHandler )
{
	m_pUppderHandler = pUpperHandler;
}

void CProtocol::RegisterErrHandler( CHandler* pHandler )
{
	m_pErrHandler = pHandler;
}

int CProtocol::send( CPackage* package )
{
	return 0;
}

int CProtocol::GetReserverLen() const
{
	return m_reservelen;
}

unsigned int CProtocol::GetActiveID()
{
	return m_activeid;
}

int CProtocol::HandlePackage( CPackage* pPackage,CProtocol* protocol )
{
	return 0;
}

void CProtocol::AddUpper( CProtocol* pUpper )
{
	if(pUpper != NULL)
	{
		m_UpperMap.insert(pair<unsigned int,CProtocol*>(pUpper->GetActiveID(),pUpper));
	}

}

CProtocol* CProtocol::GetUpper( unsigned int activeid )
{
	if(m_UpperMap.find(activeid) != m_UpperMap.end())
	{
		return m_UpperMap[activeid];
	}
	return NULL;
}

CProtocol* CProtocol::RemoveUpper( unsigned int activeid )
{   map<unsigned int,CProtocol*>::iterator ret = m_UpperMap.find(activeid);
	CProtocol* upper =NULL;
	if (ret != m_UpperMap.end())
	{
		upper = (ret->second);
		m_UpperMap.erase(ret);
	}
	return upper;
}

CProtocol* CProtocol::GetLower()
{
	return p_lower;
}

int CProtocol::Pop( CPackage* package )
{
	return 0;
}

int CProtocol::OnRecvErrPackage( CPackage* package )
{
	return 0;
}

void CProtocol::NotifyErr( int msg,unsigned int dwParam, void* pParam )
{
	return;
}

int CProtocol::Push( CPackage* package,CProtocol* protocol )
{
	return 0;
}

void CProtocol::SetActiveID( unsigned int activeid )
{
	m_activeid = activeid;
}

