#include "channelpackage.h"
#include "Log.h"

CChannelPackage::CChannelPackage( int maxlength )
{
	ConstructAlloc(maxlength,0);
}

CChannelPackage::~CChannelPackage()
{

}

int CChannelPackage::ReadFromChannel( CChannel* channel )
{
	///http://www.linuxidc.com/Linux/2014-11/109545.htm
	int ret = 0;
	if(channel->GetService()->GetNChannel() == SOCK_STREAM)
	{
		int len =  m_head-m_pPackageBuf->Data();
		//�������ƶ���Data��
		memmove(m_pPackageBuf->Data(),m_head,Length());
		m_head -=len;
		m_end -= len;

		int avalen =  m_pPackageBuf->Length()-Length();
		ret =  channel->Read(avalen,m_end);
		if(ret >0)
			m_end += ret;

	}
	else///UDPЭ���ǻ��ڱ��ĵġ�����ÿ��ֻ�ܶ�ȡһ��������package
	{
		m_end = m_head =  m_pPackageBuf->Data();///?????
		ret =  channel->Read(m_pPackageBuf->Length(),m_end);
		if(ret > 0)
			m_end += ret;
	}
	return ret;
}

int CChannelPackage::GetActiveID()
{
	return 0;
}

int CChannelPackage::ValidPackage()
{
	return Length();
}
