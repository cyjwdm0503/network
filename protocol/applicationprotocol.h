/**
执行application的协议，主要为应用层协议。因此无底层逻辑的协议
**/
#ifndef PROTOCOL_APPLICATIONPROTOCOL_H
#define PROTOCOL_APPLICATIONPROTOCOL_H

#include "Protocol.h"
const int ACTIVEID_APPLICATION = 1001;



class CApplicationProtocol:public CProtocol
{
public:
	CApplicationProtocol(CDispatcher* dispatcher);
	virtual ~CApplicationProtocol();

	//将应用层报文全部都交于对应的Session处理
	virtual int Pop( CPackage* package );

	//Session用于发送数据的接口，都通过这个接口发送
	virtual int send(CPackage* pacakge);

};


#endif