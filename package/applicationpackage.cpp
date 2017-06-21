#include "applicationpackage.h"
#include <cstring>
#include "socks.h"

CFieldIterator::CFieldIterator( char* head,char* end,CFieldDescribe* fielddesc ):m_head(head),m_end(end),m_desc(NULL)
{
	m_desc =  fielddesc;
	m_cur = m_head;
	Next();
}

bool CFieldIterator::IsEnd()
{
	if(m_end-m_cur < sizeof(m_header))
		return true;
	if(m_end-m_cur < m_header.FieldLength)
		return true;
	return false;
}

bool CFieldIterator::Next()
{
	char* m_data =  NULL;
	while(!m_data)
	{
		if(m_end-m_cur < sizeof(m_header))
			return false;

		memcpy(&m_header,m_cur,sizeof(m_header));
		{
			NetToHostShort(m_header.FieldID);
			NetToHostShort(m_header.FieldLength);
		}
		m_cur += m_header.FieldLength+sizeof(m_header);

		if(m_end-m_cur < m_header.FieldLength)
			return false;
		
		if(m_desc == NULL || m_header.FieldID == m_desc->m_FieldID)
			m_data =  m_cur;
		m_cur += m_header.FieldLength;
	}
	return true;
}

int CFieldIterator::RetrieveField(CFieldDescribe* describer,void* field )
{
	describer->StreamToClass((char*)field,m_data,m_header.FieldLength);
	return min(describer->m_ClassSize,m_header.FieldLength);
}


int CFieldIterator::RetrieveHeader( CFieldHeader& field )
{
	field.FieldID = m_header.FieldID;
	field.FieldLength = m_header.FieldLength;
	return m_header.FieldLength;
}

