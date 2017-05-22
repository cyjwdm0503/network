#include "fielddescribe.h"
#include "socks.h"

CFieldDescribe::CFieldDescribe( unsigned short FieldID,int StructSize,const char* Comment,int TotalMember,const char* FieldName,fun_callback fun)
{
	m_FieldID = FieldID;
	m_ClassSize = StructSize;
	m_StreamSize = 0;
	m_TotalMember = 0;
	fun();//执行一次内部数据位置的基础数据
}

void CFieldDescribe::SetupMember( MemberType type,int ClassOffset,int Size,const char* name )
{
	SMembererDesc* desc = (m_MemberDesc+m_TotalMember);
	strcpy(desc->name,name);
	desc->classOffset = ClassOffset;
	desc->streamOffset = m_StreamSize;//前一个字节结束是的package，字节流位置
	desc->size = Size;
	desc->type = type;
	m_StreamSize +=Size;
	m_TotalMember++;

}

void CFieldDescribe::StreamToClass( char* pField,char* pStream )
{
	for(int i=0;i < m_TotalMember;i++)
	{
		SMembererDesc* member = m_MemberDesc+i;
		memset(pField+member->classOffset,0,member->size);
		memcpy(pField+member->classOffset,pStream+member->streamOffset,member->size);
		switch (member->type)
		{
		case MT_ONE:
			break;
		case MT_TWO:
			NetToHostShort(*(pField+member->classOffset));
			break;
		case MT_FOUR:
			NetToHostLong(*(pField+member->classOffset));
			break;
		case MT_EIGHT:
			NetToHostDouble(*(pField+member->classOffset));
			break;
		default:
			break;
		}
	}
}

void CFieldDescribe::ClassToStream( char* pClass,char* pStream )
{
	for(int i=0;i < m_TotalMember;i++)
	{
		SMembererDesc* member = m_MemberDesc+i;
		memset(pStream+member->streamOffset,0,member->size);
		memcpy(pClass+member->streamOffset,pClass+member->classOffset,member->size);
		switch (member->type)
		{
		case MT_ONE:
			break;
		case MT_TWO:
			HostToNetShort(*(pStream+member->streamOffset));
			break;
		case MT_FOUR:
			HostToNetLong(*(pStream+member->streamOffset));
			break;
		case MT_EIGHT:
			HostToNetDouble(*(pStream+member->streamOffset));
			break;
		default:
			break;
		}
	}
}
