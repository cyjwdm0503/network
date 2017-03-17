#include "channelprotocol.h"

int CChannelProtocol::Push( CPackage* package,CProtocol* protocol )
{
	if(
	CProtocol::Push(package,this);
}

void CChannelProtocol::GetIds( int* readid,int* writeid )
{
	throw std::exception("The method or operation is not implemented.");
}

void CChannelProtocol::HandleInput()
{
	throw std::exception("The method or operation is not implemented.");
}

void CChannelProtocol::HandleOupt()
{
	throw std::exception("The method or operation is not implemented.");
}

void CChannelProtocol::OnTimer( int event )
{
	throw std::exception("The method or operation is not implemented.");
}

CChannelProtocol::CChannelProtocol( CSelectReactor* reactor,CChannel* channel,int maxPackageSize ):CProtocol(reactor,NULL,NULL,0),m_channel(channel),m_channelpackage(maxPackageSize)
{
	;
}

CChannelProtocol::~CChannelProtocol()
{
	
}

