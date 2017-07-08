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
	HostToNetShort(ContentLength);
	HostToNetShort(CommPhaseNo);
	HostToNetShort(SubjectID);
	HostToNetShort(FrontSubjectID);
	HostToNetShort(Tid);
	HostToNetDouble(SequenceNo);
	HostToNetDouble(RequestID);
	HostToNetDouble(SessionID);
	HostToNetDouble(FrontSeqNo);
	HostToNetDouble(CompSeqNo);
	HostToNetDouble(ActiveID);
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
