#include "contentpackage.h"
#include "socks.h"

void CContentHeadType::NetToHost()
{
	NetToHostLong(Type);
	NetToHostLong(ExtensionLen);
	NetToHostLong(Length);
}

void CContentHeadType::HostToNet()
{
	HostToNetLong(Type);
	HostToNetLong(ExtensionLen);
	HostToNetLong(Length);
}

void CContentPackage::Clear()
{
	CPackage::Clear();
}

int CContentPackage::GetActiveID()
{
	return m_contenthead.Type;
}

int CContentPackage::ValidPackage()
{
	if(CONTENTHEADLENGTH > Length())
		return -1;
	
	//读取head
	m_contenthead.FromStream(m_head);
	if(m_contenthead.Length < 0 || m_contenthead.Length > MAX_CONTENT_PACKAGE_LEN )
		return -2;

	if(m_contenthead.ExtensionLen <0 || (m_contenthead.ExtensionLen >0 && m_contenthead.ExtensionLen>CONTENTEXTHEADLENGTH))
		return -3;

	//组装exthead
	if(m_contenthead.ExtensionLen >0)
		memcpy(&m_contentexthead,m_head+CONTENTHEADLENGTH,m_contenthead.ExtensionLen);
	else
		m_contentexthead.Init();
	
	//组装对应的内容报文
	if(m_contenthead.ExtensionLen+m_contenthead.Length+CONTENTHEADLENGTH <= Length())
	{
		m_end = m_head+m_contenthead.ExtensionLen+m_contenthead.Length+CONTENTHEADLENGTH;
		Pop(CONTENTHEADLENGTH+m_contenthead.ExtensionLen);
		return m_contenthead.ExtensionLen+m_contenthead.Length+CONTENTHEADLENGTH;
	}
	return -1;

}

int CContentPackage::MakePackage()
{
	char *buf;
	m_contenthead.Length = Length();
	//先把扩展报文头写进去
	if(m_contentexthead.Tag != CONTENTEXTTAGNANO)
	{
		m_contenthead.ExtensionLen = CONTENTEXTHEADLENGTH /*+ m_contentexthead.TagLen*/;
		buf = Push(m_contenthead.ExtensionLen);
		memcpy(buf, &m_contentexthead, m_contenthead.ExtensionLen);
	}
	else
	{
		m_contenthead.ExtensionLen = 0;
	}

	//开始写报文头
	buf = Push(CONTENTHEADLENGTH);
	if(buf == NULL)
	{
		return -1;
	}

	m_contenthead.ToStream(buf);

	//	DEBUG_LOG0("CXMPPackage::MakePackage End\n");
	return 0;
}

CContentPackage::CContentPackage()
{
	m_contenthead.Init();
	m_contentexthead.Init();
}

CContentPackage::~CContentPackage()
{

}

CContentHeadType * CContentPackage::GetContentHeader()
{
		return &m_contenthead;
}

int CContentPackage::GetBodyLength()
{
		return m_contenthead.Length;
}

unsigned int CContentPackage::GetExtensionLen()
{
		return m_contenthead.ExtensionLen;
}

unsigned int CContentPackage::GetExtTag()
{
		return m_contentexthead.Tag;
}

unsigned int CContentPackage::GetExtTagLen()
{
		return m_contentexthead.TagLen;
}

char* CContentPackage::GetExtData()
{
	return m_contentexthead.Data;
}

void CContentPackage::SetExtHeader( unsigned int Tag, unsigned int TagLen, char *pData )
{
	m_contentexthead.Tag = Tag;
	m_contentexthead.TagLen = TagLen;
	memcpy(m_contentexthead.Data,pData,TagLen);
}


