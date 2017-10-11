#include "listenermanager.h"
void CListenerManager::GetIds( int* readid,int* writeid )
{
	if(m_serverchannel != NULL)
		*readid = m_serverchannel->Getfd();
	*writeid = 0;
}

void CListenerManager::HandleInput()
{
	//内部生成channel方式有待考验，因为涉及到serverapi多线程读取channel
	CChannel* channel = AccpetConnecter();
	if(channel != NULL)
	{
		if(channel->GetService()->GetNChannel() == SOCK_DGRAM)
		{//自我不在进行自我调度
			this->RemoveHandler(this);
		}
	}
}

CListenerManager::CListenerManager( CSelectReactor* outReactor,string listenLocation ):CHandler(this)
{
	m_outReactor =  outReactor;
	m_listenLocation = listenLocation;
	m_server =  new CServer();
	m_serverchannel = NULL;
	m_serverchannel =  m_server->CreateServer(m_listenLocation.c_str());
	AddHandler(this);
}



int CListenerManager::HandleEvent( int event,DWORD dwParam,void* pParam )
{
	switch (event)
	{
	case EVENT_LISTEN_FAILED:
		break;
	default:
		break;
	}
	return CHandler::HandleEvent(event,dwParam,pParam);
}


CChannel* CListenerManager::AccpetConnecter()
{
	CChannel* channel = m_server->AcceptClient();
	if(channel != NULL)
	{
		SendAccepted(channel);
	}
	return channel;
}

void CListenerManager::SendAccepted( CChannel* channel )
{
	if(m_outReactor != NULL)
	{
		m_outReactor->PostEvent(this,EVENT_LISTEN_SUCCESS,0,(void*)channel);
	}
}

void CListenerManager::OnTimer( int event )
{

}

