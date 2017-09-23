#include "Protocol.h"

CProtocol::CProtocol( CDispatcher* reactor,CPackage* pUpperPackage,CPackage* pSendPackage,int ReserverLen ):CHandler(reactor)
{
	m_activeID=0;
	m_errHandler = NULL;
	m_uppderHandler = NULL;
	m_reserveLen = ReserverLen;
	m_sendPackage = pSendPackage;
	m_upperPackage =  pUpperPackage;
	m_lower = NULL;

}

CProtocol::~CProtocol()
{
	if(GetLower() != NULL)
	{
		((CProtocol*)GetLower())->RemoveUpper(GetActiveID());
	}
	if(m_upperMap.size() >0)
	{
		m_upperMap.clear();
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
	//�ײ㱣���ֽ�+��ǰ�㱣���ֽ�
	m_reserveLen += pLower->GetReserverLen();
	if(pLower != NULL)
	{
		pLower->AddUpper(this);
	}
	m_lower = pLower;

}

void CProtocol::RegisterUpperHandler( CProtocolCallback* pUpperHandler )
{
	m_uppderHandler = pUpperHandler;
}

void CProtocol::RegisterErrHandler( CHandler* pHandler )
{
	m_errHandler = pHandler;
}

int CProtocol::send( CPackage* package )
{
	int ret =  package->MakePackage();
	if(ret < 0)
	{
		return ret;
	}
	if(m_lower != NULL)
	{
		return m_lower->Push(package,this);
	}
	else
	{
		exit(-1);
	}
	return 0;
}

int CProtocol::GetReserverLen() const
{
	return m_reserveLen;
}

unsigned int CProtocol::GetActiveID()
{
	return m_activeID;
}

int CProtocol::HandlePackage( CPackage* pPackage,CProtocol* protocol )
{//��Pop������ϲ��Э�����eventhandler����Ҫ�ڴ˲�protocol���н��
	int ret = 0;
	while (pPackage->Length() > 0)//�˴����Է��֣�һ��channelpackageֻ�ܷ�һ��contentpackage
	{//�ϲ��package���ش˰�
		m_upperPackage->AddBuf(pPackage);
		int len =  m_upperPackage->ValidPackage();

		if(len >=0)
		{
			ret = Pop(m_upperPackage);
			if(ret <0)
			{
				break;
			}
			//��Ϊ�Ѿ��ɹ������ϲ��package���������Ҫ�ѵ�ǰ���package��������ݸ�Pop��
			pPackage->Pop(len);
		}
		else if(len == -1)
		{
			//���ݰ�δ��ȫ
			break;
		}
		else
		{
			//�������ݰ�����ʵ�ʽ�session��ְ�ܷŵ���protocol����
			OnRecvErrPackage(pPackage);
			ret=len;
			break;
		}

		m_upperPackage->BufRelease();
	}
	return ret;
}

void CProtocol::AddUpper( CProtocol* pUpper )
{
	if(pUpper != NULL)
	{
		m_upperMap.insert(pair<unsigned int,CProtocol*>(pUpper->GetActiveID(),pUpper));
	}

}

CProtocol* CProtocol::GetUpper( unsigned int activeid )
{
	if(m_upperMap.find(activeid) != m_upperMap.end())
	{
		return m_upperMap[activeid];
	}
	return NULL;
}

CProtocol* CProtocol::RemoveUpper( unsigned int activeid )
{   map<unsigned int,CProtocol*>::iterator ret = m_upperMap.find(activeid);
	CProtocol* upper =NULL;
	if (ret != m_upperMap.end())
	{
		upper = (ret->second);
		m_upperMap.erase(ret);
	}
	return upper;
}

CProtocol* CProtocol::GetLower()
{
	return m_lower;
}

int CProtocol::Pop( CPackage* package )
{
	int activeID = package->GetActiveID();
	CProtocol* upper = GetUpper(activeID);
	//���û�ж�Ӧ���ϲ�Э�鴦��������Ĭ�ϵ�handler���д���
	if(upper != NULL)
	{
		return upper->HandlePackage(package,this);
	}
	if(m_uppderHandler != NULL)
	{
		return m_uppderHandler->HandlePackage(package,this);
	}
	return 0;
}

int CProtocol::OnRecvErrPackage( CPackage* package )
{
	return 0;
}

void CProtocol::NotifyErr( int msg,unsigned int dwParam, void* pParam )
{
	if(m_errHandler != NULL)
		m_errHandler->SendEvent(msg,dwParam,pParam);
}

int CProtocol::Push( CPackage* package,CProtocol* protocol )
{
	m_sendPackage->AddBuf(package);
	int ret = m_sendPackage->MakePackage();
	if(ret == 0)
	{
		if(m_lower != NULL)
		{
			ret = m_lower->Push(m_sendPackage,this);
		}
	}
	m_sendPackage->BufRelease();
	return ret;
}

void CProtocol::SetActiveID( unsigned int activeid )
{
	m_activeID = activeid;
}

