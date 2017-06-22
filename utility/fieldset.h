#ifndef FIELDSET_H 
#define FIELDSET_H
/************************************************************************/
/* Ӧ�ò�Э�飬contentpackage��Ҫ������ȷ��ÿ������һ�����������ݰ�������û����Ӧ��ҵ��
��package��Ӧ��ҵ��ÿ��package�ڶ��Ǵ�ȡ�ķ�ҵ������ݰ���
package�������field,ÿ�η���fieldʱ����fieldǰ����һ��fieldheader��Ȼ����field���ݡ�
��packageȡ��field�Ĺ�����Ҳ��ͨ����ȡfiledheader,Ȼ��������ݸ��ơ�
ȡ�����ݵĹ�����ͨ��package��ȡһ��������������ȡ����
�������ݵĹ��̣�ÿ�λ���package����һ��ռ䣬Ȼ����д��롣
applicationpackage ����field.field�Ĺ�������Ϊfielddescribe��
*/
/************************************************************************/

#include "fielddescribe.h"
#include "Package.h"

struct CFieldHeader
{
	unsigned short FieldID;
	unsigned short FieldLength;
};

class CFieldIterator
{
public:
	//��DESCΪ��ʱ���ܹ������ڲ��ṹ�Զ��������е�Field 
	CFieldIterator(char* head,char* end,CFieldDescribe* fielddesc);
	virtual bool IsEnd();
	virtual bool Next();
	virtual int RetrieveField(CFieldDescribe* describer,void* field);
	virtual int RetrieveHeader(CFieldHeader& fieldheader);
private:
	char *m_head,*m_end;
	char *m_cur , *m_data;
	CFieldDescribe *m_desc;
	CFieldHeader m_header;
};

class CFieldSet:public CPackage
{
 
public:
	CFieldSet();
	virtual ~CFieldSet();


	 int GetSingleField(CFieldDescribe *pFieldDescribe, void *pField);
		
	 int AddField(CFieldDescribe *pFieldDescribe, void *pField);
	
	 CFieldIterator GetFieldIterator(CFieldDescribe *pFieldDescribe);

	 char * AllocField(unsigned short wFieldID,unsigned short wSize);
};

#endif