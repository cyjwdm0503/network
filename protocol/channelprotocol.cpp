#include "channelprotocol.h"
int CChannelProtocol::Push( CPackage* package,CProtocol* protocol )
{
	if(m_channel->GetService()->GetNChannel() == SOCK_STREAM && m_cacheList != NULL)
	{//TCP 只能分组转发先存储再select 准备好后，才取出来进行发送
		m_cacheList->push_back(package->Address(),package->Length());
		return 0;
	}
	else //UDP一次性发送完毕。
	{
		int len =  m_channel->Write(package->Length(),package->Address());
		if(len != package->Length())
		{//错误
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
	//用于TCP协议...因为UDP是无连接协议，任何时候都能写入。TCP需要在先判定在写入
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
{//在id准备好后。读入数据
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
		{//表示正确Pop出来一个上层Package
			return;
		}
	}
	return ;
	
}

void CChannelProtocol::HandleOutput()
{//取出缓存的数据进行发送

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
{//用于发送缓存包---目前不理解为什么不判定select是否准备好，就进行发送
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
		SetTimer(EVENT_CHANNELTIME_ID, 1000);			//打开定时强制刷新定时器
	}
}

CChannelProtocol::~CChannelProtocol()
{
	
}

