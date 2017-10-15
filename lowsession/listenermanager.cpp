#include "listenermanager.h"
void CListenerManager::GetIds(int *readid, int *writeid)
{
	if (m_serverchannel != NULL)
	{
		*readid = m_serverchannel->Getfd();
	}
	else
	{
		*readid = 0;
	}
	*writeid = 0;
}

void CListenerManager::HandleInput()
{
	//内部生成channel方式有待考验，因为涉及到serverapi多线程读取channel
	CChannel *channel = AccpetConnecter();
	if (channel != NULL)
	{
		if (channel->GetService()->GetNChannel() == SOCK_DGRAM)
		{ //自我不在进行自我调度
			this->RemoveHandler(this);
		}
	}
}

CListenerManager::CListenerManager(CSelectReactor *outReactor, string listenLocation) : CHandler(this)
{
	m_outReactor = outReactor;
	m_listenLocation = listenLocation;
	m_server = new CServer();
	m_serverchannel = NULL;

	if (!m_listenLocation.empty())
		m_serverchannel = m_server->CreateServer(m_listenLocation.c_str());

	AddHandler(this);
}

int CListenerManager::HandleEvent(int event, DWORD dwParam, void *pParam)
{
	switch (event)
	{
	case EVENT_ACCEPT_FAILED:
		break;
	default:
		break;
	}
	return CHandler::HandleEvent(event, dwParam, pParam);
}

CChannel *CListenerManager::AccpetConnecter()
{
	CChannel *channel = m_server->AcceptClient();
	if (channel != NULL)
	{
		SendAccepted(channel);
	}
	return channel;
}

void CListenerManager::SendAccepted(CChannel *channel)
{
	if (m_outReactor != NULL)
	{
		m_outReactor->PostEvent(NULL, EVENT_ACCEPT_SUCCESS, 0, (void *)channel);
	}
}

void CListenerManager::OnTimer(int event)
{
}

void CListenerManager::SetListenLocation(string connectLocation)
{
	m_listenLocation = connectLocation;
	if (m_serverchannel == NULL)
	{
		if (!m_listenLocation.empty())
			m_serverchannel = m_server->CreateServer(m_listenLocation.c_str());
	}
}

void CListenerManager::PostEvent(int event, DWORD dwParam, void *pParam)
{
	CHandler::PostEvent(event, dwParam, pParam);
}