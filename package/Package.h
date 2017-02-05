#ifndef PACKAGE_H
#define PACKAGE_H

const unsigned int PACKAGE_ID = 1;
const unsigned int CHANNELPACKAGE_ID = 2;

#include "Channel.h"
/************************************************************************/
/* 
*/
/************************************************************************/

typedef struct SPackageHead
{
	 int PACKAGEID;
	 int DATALENGTH;
	 int PACKAGELENGTH;
	 int VERSION;
}header;


class CPackage
{
public:
	CPackage();
	CPackage(unsigned int PACKAGEID,int maxlen=1024);
	virtual ~CPackage();
	//���ϲ��packageд�뵽��ǰ��
	virtual bool PushPackage(CPackage* package);
	//��ȡ��ǰpackage�������ϲ�package
	virtual bool PopPackage(CPackage* package);

	//���ϲ�packageд��ʱ��push�ϲ�package������ͷ���Ա�GetPackage����ȷȡ���ϲ�Package
	void PushHeader();
	bool PopHeader();
	//����m_data������ֵ����װ��ǰ���Package
	virtual void MakePackage();

	//��ȡheader
	header* GetHeader();

	//��ȡ���ݵ���ʼ��ַ
	char* GetDataPtr();
	char* GetPackagePtr();

	//��ȡ���ݵĳ���
	unsigned int GetDataLen() const;
	unsigned int GetPackageLen() const;

	//���Զ�ȡ���������
	unsigned int GetValidLength() const;

	//���ڵײ��ȡָ�룬��ȡ����
	char* GetValidDataPtr();

protected:
	


	char* m_data;
	char* begin;
	char* cur;
	char* end;
	unsigned int m_maxlen;
	header m_header; 
};

#endif