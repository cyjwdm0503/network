/**
ִ��application��Э�飬��ҪΪӦ�ò�Э�顣����޵ײ��߼���Э��
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

	//��Ӧ�ò㱨��ȫ�������ڶ�Ӧ��Session����
	virtual int Pop( CPackage* package );

	//Session���ڷ������ݵĽӿڣ���ͨ������ӿڷ���
	virtual int send(CPackage* pacakge);

};


#endif