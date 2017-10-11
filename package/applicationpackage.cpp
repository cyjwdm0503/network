#include "applicationpackage.h"
#include <cstring>
#include "socks.h"


void CApplicationPackageHeader::FromStream( char *pStream )
{
	memcpy(this, pStream, sizeof(CApplicationPackageHeader));
	NetToHostShort(ContentLength);
	NetToHostShort(CommPhaseNo);
	NetToHostShort(SubjectID);
	NetToHostShort(FrontSubjectID);
	NetToHostShort(Tid);
	NetToHostLong(SequenceNo);
	NetToHostLong(RequestID);
	NetToHostLong(SessionID);
	NetToHostLong(FrontSeqNo);
	NetToHostLong(CompSeqNo);
	NetToHostLong(ActiveID);
}

void CApplicationPackageHeader::ToStream( char *pStream )
{
	memcpy(pStream, this, sizeof(CApplicationPackageHeader));
	HostToNetShort(((CApplicationPackageHeader*)pStream)->ContentLength);
	HostToNetShort(((CApplicationPackageHeader*)pStream)->CommPhaseNo);
	HostToNetShort(((CApplicationPackageHeader*)pStream)->SubjectID);
	HostToNetShort(((CApplicationPackageHeader*)pStream)->FrontSubjectID);
	HostToNetShort(((CApplicationPackageHeader*)pStream)->Tid);
	HostToNetLong(((CApplicationPackageHeader*)pStream)->SequenceNo);
	HostToNetLong(((CApplicationPackageHeader*)pStream)->RequestID);
	HostToNetLong(((CApplicationPackageHeader*)pStream)->SessionID);
	HostToNetLong(((CApplicationPackageHeader*)pStream)->FrontSeqNo);
	HostToNetLong(((CApplicationPackageHeader*)pStream)->CompSeqNo);
	HostToNetLong(((CApplicationPackageHeader*)pStream)->ActiveID);
}


CApplicationPackageHeader::CApplicationPackageHeader()
{
	memset(this, 0 ,sizeof(CApplicationPackageHeader));
}


int CApplicationPackage::GetActiveID()
{
	return m_ApplicationHeader.ActiveID; 
}

int CApplicationPackage::ValidPackage()
{
	 if(APPLICATIONHEADERLENGTH >Length())
		 return -1;
	 m_ApplicationHeader.FromStream(m_head);
	 Pop(APPLICATIONHEADERLENGTH);
	 Truncate(m_ApplicationHeader.ContentLength);
	 return m_ApplicationHeader.ContentLength+APPLICATIONHEADERLENGTH;

}

int CApplicationPackage::MakePackage()
{
	char* buf = NULL;
	m_ApplicationHeader.ContentLength = Length();
	buf =  Push(APPLICATIONHEADERLENGTH);
	if(buf == NULL)
		return -1;
	m_ApplicationHeader.ToStream(buf);
	return 0;
}

bool CApplicationPackage::CopyPackage( CPackage* pPackage )
{
	
	CApplicationPackage* appPackage =  dynamic_cast<CApplicationPackage*>(pPackage);
	if(appPackage !=  NULL)
	{
		m_ApplicationHeader = appPackage->m_ApplicationHeader;
	}
	return CFieldSet::CopyPackage(pPackage);
}
