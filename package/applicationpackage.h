#ifndef APPLICATIONPACKAGE_H 
#define APPLICATIONPACKAGE_H
/************************************************************************/
/* Ӧ�ò�Э�飬contentpackage��Ҫ������ȷ��ÿ������һ�����������ݰ�������û����Ӧ��ҵ��
��package��Ӧ��ҵ��ÿ��package�ڶ��Ǵ�ȡ�ķ�ҵ������ݰ���
package�������field,ÿ�η���fieldʱ����fieldǰ����һ��fieldheader��Ȼ����field���ݡ�
��packageȡ��field�Ĺ�����Ҳ��ͨ����ȡfiledheader,Ȼ��������ݸ��ơ�
ȡ�����ݵĹ�����ͨ��package��ȡһ��������������ȡ����
�������ݵĹ��̣�ÿ�λ���package����һ��ռ䣬Ȼ����д��롣
*/
/************************************************************************/
class CFieldHeader
{
public:
	unsigned short FieldID;
	unsigned short FiledLength;
	CFieldHeader();
	
};
#endif