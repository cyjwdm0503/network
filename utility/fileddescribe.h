/************************************************************************/
/* 
��������field���ࡣ���ֽ�������ȡ���ݣ���Ҫ֪��ÿ��field������״�������ܴ���ȡ������*/
//��ҪĿ����Ϊ�˱�����뵼�µĴ��������Ҫͳ��ÿ��member��ʵ�ʳ��ȡ��Լ����package���и��Ե�ƫ��λ��
//field�Ĵ�ȡ���򡣡���������field. field�ڴ���ʱ��Ҫ���ɶ�Ӧ�ĵ�fielddescribe������Ӧpackageͨ��������ȡ��Ӧ�����ݵ�һ��fieldָ����
/************************************************************************/
#ifndef FIELDDESCRIBE_H
#define FIELDDESCRIBE_H
#include <cstring>
#include "typedef.h"


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
	typedef void (*fun_callback)();
public:
	CFieldDescribe(unsigned short FieldID,int StructSize,const char* Comment,int TotalMember,const char* FieldName,fun_callback fun);

	unsigned short m_FieldID;
	int m_ClassSize;
	int m_PackageSize;
	char m_Comment[127];
	int m_TotalMember;
	char m_FieldName[127];
	SMembererDesc m_MemberDesc[100];

	inline void SetupMember(MemberType type,int ClassOffset,int Size,const char* name);
	
	//���ö�Ӧ���ݳ�Ա��ռλ��Ϣ��
	void SetupMember(CBaseStringType&,int ClassOffset,int Size,const char* name )
	{
		SetupMember(MT_ONE,  ClassOffset,  Size,    name);
	}
	void SetupMember(CBaseIntTpye&,int ClassOffset,int Size,const char* name )
	{
		SetupMember(MT_FOUR,  ClassOffset,  Size,    name);
	}
	void SetupMember(CBaseDoubleType&,int ClassOffset,int Size,const char* name )
	{
		SetupMember(MT_EIGHT,  ClassOffset,  Size,    name);
	}
	void SetupMember(CBaseCharType&,int ClassOffset,int Size,const char* name )
	{
		SetupMember(MT_ONE,  ClassOffset,  Size,    name);
	}
	void SetupMember(CBaseShortType&,int ClassOffset,int Size,const char* name )
	{
		SetupMember(MT_TWO,  ClassOffset,  Size,    name);
	}
};

CFieldDescribe::CFieldDescribe( unsigned short FieldID,int StructSize,const char* Comment,int TotalMember,const char* FieldName,fun_callback fun)
{
	m_FieldID = FieldID;
	m_ClassSize = StructSize;
	m_PackageSize = 0;
	m_TotalMember = 0;
	fun();//ִ��һ���ڲ�����λ�õĻ�������
}

void CFieldDescribe::SetupMember( MemberType type,int ClassOffset,int Size,const char* name )
{
	SMembererDesc* desc = (m_MemberDesc+m_TotalMember);
	strcpy(desc->name,name);
	desc->classOffset = ClassOffset;
	desc->packageOffset = m_PackageSize;//ǰһ���ֽڽ����ǵ�package���ֽ���λ��
	desc->size = Size;
	desc->type = type;
	m_PackageSize +=Size;
	m_TotalMember++;

}

#ifdef  TEST_FIELD

class TESTField
{
public:
	CBaseIntTpye m_int;
	CBaseShortType m_short;
	CBaseStringType m_string;
	CBaseCharType m_char;
	CBaseDoubleType m_double;
	void DescriberMember()
	{
		m_Describe.SetupMember(m_int,(char*)&m_int-(char*)this,sizeof(m_int),"m_int");
		m_Describe.SetupMember(m_short,(char*)&m_short-(char*)this,sizeof(m_short),"m_short");
		m_Describe.SetupMember(m_string,(char*)&m_string-(char*)this,sizeof(m_short),"m_string");
	}
	static CFieldDescribe m_Describe;
	
};
static void Make_TESTField(){TESTField field;field.DescriberMember();};
CFieldDescribe TESTField::m_Describe(1,sizeof(TESTField),"������",0,"TestField",Make_TESTField);
//CFieldDescribe TESTField::m_Describe(12,sizeof(TESTField),"�����Ľ���",0,"����",Make_TESTField);
#endif

#define  TYPE_DESC(member)  m_Describe.SetupMember(member,(char*)&member-(char*)this,sizeof(member), #member)
#define	 FIELD_DESC(member)	void DescriberMember(){ member; }	static CFieldDescribe m_Describe
#define  MAKGE_FIELD_DESC(FIELD,FIELDID,NAME) static void Make_##FIELD() {FIELD field; field.DescriberMember();} CFieldDescribe FIELD::m_Describe(FIELDID,sizeof(FIELD), NAME ,0, #FIELD ,Make_##FIELD);

//���÷�ʽΪFILED_DESC(TYPE(m_int); TYPE(m_short);......);//��Ա������Ҫ�̳����������




#endif