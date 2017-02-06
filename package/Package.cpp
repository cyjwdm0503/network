#include "Package.h"
#include <cstdlib>
#include <cstring>
#include "Log.h"


CPackage::CPackage():m_data(NULL),begin(NULL),end(NULL),cur(NULL),m_maxlen(0)
{
	m_header.PACKAGEID=0;
	m_header.PACKAGELENGTH = sizeof(header);
	m_header.DATALENGTH = 0;
}

CPackage::CPackage( unsigned int PACKAGEID,int maxlen/*=1024*/ ):m_data(NULL),begin(NULL),end(NULL),cur(NULL),m_maxlen(0)
{
	m_header.PACKAGEID=PACKAGEID;
	m_header.PACKAGELENGTH = sizeof(header);
	m_header.DATALENGTH = 0;
	m_data = new char [maxlen+sizeof(header)];
	begin = m_data;
	end =  m_data+sizeof(header);
	cur =  m_data+sizeof(header);
	m_maxlen =  maxlen;
}


CPackage::~CPackage()
{
	;
}

bool CPackage::PushPackage( CPackage* package )
{
	if(GetValidLength()<package->GetPackageLen())
	{
		return false;
	}
	memcpy(cur,package->GetPackagePtr(),package->GetPackageLen());
	
	//cur +=package->GetPackageLen();
	cur += package->GetPackageLen();
	end = cur;

	m_header.DATALENGTH += package->GetPackageLen();
	m_header.PACKAGELENGTH  =  m_header.DATALENGTH+sizeof(header);
	PushHeader();

	return true;
}

bool CPackage::PopPackage( CPackage* package )
{
	if(GetDataLen() < sizeof(header))
		return false;
	
	header head;
	memcpy(&head,cur,sizeof(header));
	
	if(GetPackageLen()< head.PACKAGELENGTH)
		return false;
	
	memcpy(package->GetPackagePtr(),cur,head.PACKAGELENGTH);
	cur +=head.PACKAGELENGTH;
	return true;
}

void CPackage::PushHeader()
{
	memcpy(begin,&m_header,sizeof(header));
}

void CPackage::MakePackage()
{
	PopHeader();
	GetHeader();
	begin =  m_data;
	cur =  m_data+sizeof(header);
	end =  begin+m_header.PACKAGELENGTH;

	m_maxlen = end-cur;
}

header* CPackage::GetHeader()
{
	if(GetPackageLen() >= sizeof(header))
	{
		return &m_header;
	}
	else
	{
		return NULL;
	}
}

char* CPackage::GetDataPtr()
{
	return cur;
}

char* CPackage::GetPackagePtr()
{
	return begin;
}

int CPackage::GetDataLen() const
{
	return max(end-cur,0);
}

int CPackage::GetPackageLen() const
{
	return max(end-begin,0);
}



int CPackage::GetValidLength() const
{
	return m_maxlen-(max(end-cur,0));
}

char* CPackage::GetValidDataPtr()
{
	return end;
}

bool CPackage::PopHeader()
{
	if(GetPackageLen() < sizeof(header))
		return false;
	
	memcpy(&m_header,m_data,sizeof(header));
	return true;
}
