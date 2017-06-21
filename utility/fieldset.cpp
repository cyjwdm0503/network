#include "fieldset.h"
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
	return min(describer->m_StreamSize,m_header.FieldLength);
}


int CFieldIterator::RetrieveHeader( CFieldHeader& field )
{
	field.FieldID = m_header.FieldID;
	field.FieldLength = m_header.FieldLength;
	return m_header.FieldLength;
}


CFieldSet::CFieldSet():CPackage()
{

}

CFieldSet::~CFieldSet()
{

}

int CFieldSet::GetSingleField( CFieldDescribe *pFieldDescribe, void *pField )
{

}

int CFieldSet::AddField( CFieldDescribe *pFieldDescribe, void *pField )
{
	char* data =  AllocField(pFieldDescribe->m_FieldID,pFieldDescribe->m_StreamSize);
	pFieldDescribe->ClassToStream((char*)pField,data);
	return pFieldDescribe->m_StreamSize;
}

CFieldIterator CFieldSet::GetFieldIterator( CFieldDescribe *pFieldDescribe )
{
	return CFieldIterator(m_head,m_end,pFieldDescribe);
}

char * CFieldSet::AllocField( unsigned short wFieldID,unsigned short wSize )
{
	if(m_end+sizeof(CFieldHeader)+ wSize >m_pPackageBuf->Data()+m_pPackageBuf->Length())
		return NULL;

	CFieldHeader header;
	header.FieldID = wFieldID;
	header.FieldLength = wSize;
	HostToNetShort(header.FieldID);
	HostToNetShort(header.FieldLength);

	memcpy(m_end,&header,sizeof(header));
	char* fielddata =  m_end+sizeof(header);
	m_end = fielddata+wSize;

	return fielddata;
}
