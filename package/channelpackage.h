///channelpackage���������udp����tcpЭ�����յ��������ַ�
//���Ա�֤�����ܹ���ȷ�յ�
//��װ��Ӧ���ݰ���Ϊ�ϲ�Э��Ĺ���
//�ڶ�Ӧ��·��TCPʱ�����ڲ��ܱ�֤ÿ�ζ�����ȷ������package����Ҫ�и�Protocol������channelpackage�Ļ���������𷢳������
//��UDP�£�����Ҫ���иû���Ĺ���
/////http://www.linuxidc.com/Linux/2014-11/109545.htm
////���д�ò����ݰ�ʱ��Ӧ��д�뻺�棬��ӻ���ȡ����д���²㡣
//UDP�����ֱ��д


#ifndef CHANNELPACKAGE_H
#define CHANNELPACKAGE_H


#include "Package.h"
#include "Channel.h"

class CChannelPackage:public CPackage
{
public:
	CChannelPackage(int maxlength);
	
	virtual ~CChannelPackage();
	int ReadFromChannel(CChannel* channel);

	virtual int GetActiveID();

	virtual int ValidPackage();

};

//typedef struct HEADER
//{
//	int ivalue;
//	double dvalue;
//	char sbuf[20];
//}HeaderType;
//
//class CTestPackage:public CPackage
//{
//public:
//	CTestPackage();
//
//private:
//	HeaderType m_head;
//};
#endif // !CHANNELPACKAGE_H
