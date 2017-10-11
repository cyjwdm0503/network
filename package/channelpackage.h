///channelpackage用来缓存从udp或者tcp协议中收到的数据字符
//用以保证数据能够正确收到
//组装对应数据包，为上层协议的功能
//在对应链路是TCP时，由于不能保证每次都能正确发送完package。需要有个Protocol来进行channelpackage的缓存管理。负责发出与读入
//在UDP下，不需要进行该缓存的管理
/////http://www.linuxidc.com/Linux/2014-11/109545.htm
////因此写该层数据包时，应先写入缓存，后从缓存取出，写入下层。
//UDP则可以直接写


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
