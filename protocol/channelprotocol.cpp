#include "channelprotocol.h"
int CChannelProtocol::Push( CPackage* package,CProtocol* protocol )
{
	if(m_channel->GetService()->GetNChannel() == SOCK_STREAM && m_cacheList != NULL)
	{//TCP ֻ�ܷ���ת���ȴ洢��select ׼���ú󣬲�ȡ�������з���
		m_cacheList->push_back(package->Address(),package->Length());
		return 0;
	}
	else //UDPһ���Է�����ϡ�
	{
		int len =  m_channel->Write(package->Length(),package->Address());
		if(len != package->Length())
		{//����
			return -1;
		}
	}
	return 0;
}

void CChannelProtocol::GetIds( int* readid,int* writeid )
{
	if(m_channel!=NULL && !m_channel->Available())
	{
		*readid = 0;
		*writeid = 0;
		return ;
	}
	if(m_channel != NULL)
	{
		*readid =  m_channel->Getfd();
	}
	else
	{
		*readid = 0;
	}

	if(m_cacheList == NULL)
		*writeid = m_channel->Getfd();
	//����TCPЭ��...��ΪUDP��������Э�飬�κ�ʱ����д�롣TCP��Ҫ�����ж���д��
	else
	{
		if( !m_cacheList->is_empty())
		{
			*writeid = m_channel->Getfd();
		}
		else
		{
			*writeid = 0;
		}
	}

}

void CChannelProtocol::HandleInput()
{//��id׼���ú󡣶�������
	int ret = 0;
	for(int i=0;i <10; i++)
	{
		int readlen =  m_channelPackage.ReadFromChannel(m_channel);
		if(readlen <0)
		{
			NotifyErr(EVENT_CHANNEL_READ_ERRO,0,this);
			return ;
		}
		if(readlen == 0)
		{
			break;
		}
		ret = Pop(&m_channelPackage);
		if(ret != 0)
		{//��ʾ��ȷPop����һ���ϲ�Package
			return;
		}
	}
	return ;
	
}

void CChannelProtocol::HandleOutput()
{//ȡ����������ݽ��з���

	if(!m_channel->Available())
	{
		return ;
	}
	for(int i=0; i<10; i++)
	{
		int outlen = 4096;
		int successlen = 0;
		void* ptr = m_cacheList->get_data(outlen);
		if(outlen>0)
		{
			successlen = m_channel->Write(outlen,(char*)ptr);
			if(successlen <0)
			{
				NotifyErr(EVENT_CHANNEL_WRITE_ERRO,0,this);
				return;
			}
			m_cacheList->pop_front(successlen);
			if(successlen != outlen)
			{
				break;
			}
			
		}
	}
	return;	
}

void CChannelProtocol::OnTimer( int event )
{//���ڷ��ͻ����---Ŀǰ�����Ϊʲô���ж�select�Ƿ�׼���ã��ͽ��з���
	if(event == EVENT_CHANNELTIME_ID)
		HandleOupt();
}

CChannelProtocol::CChannelProtocol( CDispatcher* reactor,CChannel* channel,int maxPackageSize ):CProtocol(reactor,NULL,NULL,0),m_channel(channel),m_channelPackage(maxPackageSize)
{
#ifdef DEBUG
	m_cacheList =  NULL
#endif

#ifndef DEBUG
	m_cacheList = new CCacheList();
#endif

	if (m_cacheList != NULL && m_channel->GetService()->GetNChannel() == SOCK_STREAM)
	{
		SetTimer(EVENT_CHANNELTIME_ID, 1000);			//�򿪶�ʱǿ��ˢ�¶�ʱ��
	}
}

CChannelProtocol::~CChannelProtocol()
{
	
}

