#ifndef APPLICATIONPACKAGE_H 
#define APPLICATIONPACKAGE_H
#include "Package.h"
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
struct CFieldHeader
{
	unsigned short FieldID;
	unsigned short FieldLength;
};

class CFieldIterator
{
public:
	CFieldIterator(char* head,char* end,CF);
};

class CFieldSet:public CPackage
{

};

#endif