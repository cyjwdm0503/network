/**
执行application的协议，主要为应用层协议。因此无底层逻辑的协议
**/
#ifndef APPLICATIONPROTOCOL_H
#define APPLICATIONPROTOCOL_H

#include "Protocol.h"
const int ACTIVEID_APPLICATION = 1001;
class CApplicationProtocol:public CProtocol
{
public:
	CApplicationProtocol(CDispatcher* dispatcher);
	virtual ~CApplicationProtocol();

	virtual int Pop( CPackage* package );


	//处理消息
	 

};


#endif