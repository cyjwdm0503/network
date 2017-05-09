/************************************************************************/
/* 
��������field���ࡣ���ֽ�������ȡ���ݣ���Ҫ֪��ÿ��field������״�������ܴ���ȡ������*/
//��ҪĿ����Ϊ�˱�����뵼�µĴ��������Ҫͳ��ÿ��member��ʵ�ʳ��ȡ��Լ����package���и��Ե�ƫ��λ��
/************************************************************************/
#ifndef FIELDDESCRIBE_H
#define FIELDDESCRIBE_H
#include <cstring>

class CBaseStringType
{
};

class CBaseIntTpye 
{
};

class CBaseDoubleType
{

};
class CBaseCharType
{

};

class CBaseShortType
{

};

enum MemberType
{
	MT_ONE,
	MT_TWO,
	MT_FOUR,
	MT_EIGHT
};
struct SMembererDesc
{
	MemberType type;//��Ա����������---�������ֽ���ת��
	int classOffset;//�����е�ƫ����
	int packageOffset;//��package�е�ƫ����
	int size;//���ݳ���
	char name[30];//�������Ƴ���
};

class CFieldDescribe
{
	CFieldDescribe(unsigned short FieldID,int StructSize,const char* Comment,int TotalMember,const char* FieldName);
public:
	unsigned short m_FieldID;
	int m_StructSize;
	int m_PackageSize;
	char m_Comment[127];
	int m_TotalMember;
	char m_FieldName[127];
	SMembererDesc m_MemberDesc[100];

	inline void SetupMember(MemberType type,int ClassOffset,int PackageOffset,int Size,const char* name);
	void SetupMember(CBaseStringType&,int ClassOffset,int PackageOffset,int Size,const char* name )
	{
		SetupMember(MT_ONE,  ClassOffset,  PackageOffset,  Size,    name);
	}
	void SetupMember(CBaseIntTpye&,int ClassOffset,int PackageOffset,int Size,const char* name )
	{
		SetupMember(MT_FOUR,  ClassOffset,  PackageOffset,  Size,    name);
	}
	void SetupMember(CBaseDoubleType&,int ClassOffset,int PackageOffset,int Size,const char* name )
	{
		SetupMember(MT_EIGHT,  ClassOffset,  PackageOffset,  Size,    name);
	}
	void SetupMember(CBaseCharType&,int ClassOffset,int PackageOffset,int Size,const char* name )
	{
		SetupMember(MT_ONE,  ClassOffset,  PackageOffset,  Size,    name);
	}
	void SetupMember(CBaseShortType&,int ClassOffset,int PackageOffset,int Size,const char* name )
	{
		SetupMember(MT_TWO,  ClassOffset,  PackageOffset,  Size,    name);
	}
};

CFieldDescribe::CFieldDescribe( unsigned short FieldID,int StructSize,const char* Comment,int TotalMember,const char* FieldName )
{
	m_FieldID = 0;
	m_StructSize = 0;
	m_PackageSize = 0;
	m_TotalMember = 0;
}

void CFieldDescribe::SetupMember( MemberType type,int ClassOffset,int PackageOffset,int Size,const char* name )
{
	SMembererDesc* desc = (m_MemberDesc+m_TotalMember);
	strcpy(desc->name,name);
	desc->classOffset = ClassOffset;
	desc->packageOffset = PackageOffset;
	desc->size = Size;
	desc->type = type;
	m_PackageSize +=Size;
	m_TotalMember++;

}

#endif