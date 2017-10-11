/************************************************************************/
/* 
用于描述field的类。从字节流里面取数据，需要知道每个field的描述状况，才能从中取出数据*/
//主要目的是为了避免对齐导致的错误。因此需要统计每个member的实际长度。以及类和package流中各自的偏移位置
//field的存取规则。。用于描述field. field在创建时就要生成对应的的fielddescribe。。对应package通过描述存取对应的内容到一个field指针中
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
	MemberType type;//成员变量的类型---用来做字节序转换
	int classOffset;//在类中的偏移量
	int streamOffset;//在package中的偏移量
	int size;//数据长度
	char name[30];//数据名称长度
};

class CFieldDescribe
{
	typedef void (*fun_callback)();
public:
	CFieldDescribe(unsigned short FieldID,int ClassSize,const char* Comment,int TotalMember,const char* FieldName,fun_callback fun);



	void SetupMember(MemberType type,int ClassOffset,int Size,const char* name);
	
	//设置对应数据成员的占位信息等
	void SetupMember(CBaseStringType&,int ClassOffset,int Size,const char* name );
	void SetupMember(CBaseIntTpye&,int ClassOffset,int Size,const char* name );
	void SetupMember(CBaseDoubleType&,int ClassOffset,int Size,const char* name );
	void SetupMember(CBaseCharType&,int ClassOffset,int Size,const char* name );
	void SetupMember(CBaseShortType&,int ClassOffset,int Size,const char* name );
	
	void StreamToClass(char* pField,char* pStream,int streamSize);
	void ClassToStream(char* pClass,char* pStream);


	unsigned short m_FieldID;
	int m_ClassSize;
	int m_StreamSize;
	char m_Comment[127];
	int m_TotalMember;
	char m_FieldName[127];
	SMembererDesc m_MemberDesc[100];
};



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
CFieldDescribe TESTField::m_Describe(1,sizeof(TESTField),"测试类",0,"TestField",Make_TESTField);
//CFieldDescribe TESTField::m_Describe(12,sizeof(TESTField),"类名的解释",0,"类名",Make_TESTField);
#endif

#define  TYPE_DESC(member)  m_Describe.SetupMember(member,(char*)&member-(char*)this,sizeof(member), #member)
#define	 FIELD_DESC(member)	void DescriberMember(){ member; }	static CFieldDescribe m_Describe


// 全局静态变量。用于生成对应的描述的信息
#define  MAKGE_FIELD_DESC(FIELD,FIELDID,NAME) static void Make_##FIELD() {FIELD field; field.DescriberMember();} CFieldDescribe FIELD::m_Describe(FIELDID,sizeof(FIELD), NAME ,0, #FIELD ,Make_##FIELD);

//调用方式为FILED_DESC(TYPE(m_int); TYPE(m_short);......);//成员类型需要继承与基础类型




#endif