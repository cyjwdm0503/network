/************************************************************************/
/* 
具有一个完整package的protocol 
此成会维护对应的contentpackage.同提供给上层应用层的接口;
主要是上层协议XXXXProtocol利用Protocol.Send()写入到CContentProtocol层。
CContentProtocol.Push()会写入到CChannelProtocol
进行缓存，或者直接发送。

见contentprotocol的send与push的描述

*/
/************************************************************************/

#ifndef CONTENTPROTOCOL_H 
#define CONTENTPROTOCOL_H

#include "Protocol.h"


class CContentProtocol:public CProtocol
{
public:
	CContentProtocol(CSelectReactor* reactor);
	virtual ~CContentProtocol();

	virtual int Pop( CPackage* package );

	virtual int OnRecvErrPackage( CPackage* package );

	//向channelprotocol传送package时，添加content层的头部。
	virtual int Push( CPackage* package,CProtocol* protocol );

	virtual void OnTimer( int event );
	
	//发送timeout到对方，进行设置
	void send_timeout(int timeout);

	//利用收到的CContentPackage设置对应的心跳超时时间
	void set_timeout(CPackage* package);

	//不进行心跳的测试
	void set_timecheck(bool flag);
private:
	int m_timeOut;
	bool m_checktime;
};


#endif
