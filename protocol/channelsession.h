/************************************************************************/
/* ���ڴ���channelprotocol�����Ϣ�����Լ�������Ϣ�����session
��ΪsessionҲ�Ǳ��¼����ȵ��࣬���Ҫ�̳���CHandler
��Ϊ�Ժ�����ṩ�Ķ���session����������ӿڣ����Ҫ��channel���з�װ

Ϊ�����ṩ�Զ���Ļص������ṩһ���ص�����
*/
/************************************************************************/
#ifndef CHAANELSESSION_H
#define CHANNELSESSION_H

#include "channelprotocol.h"
#include "Handler.h"

class CSessionCallback
{
public:
	virtual void OnReadError(int ErrorCode){};
	virtual void OnWriteError(int ErrorCode){};
	virtual void OnDisconnected(int ErrorCode){};
	virtual void OnConnected(int Code){};
};

class CSession:public CHandler
{
public:
	CSession(CDispatcher *selecter,CChannel *pChannel,int MaxPackageSize);
	~CSession();

	virtual void GetIds( int* readid,int* writeid );


	virtual int HandleEvent( int event,DWORD dwParam,void* pParam );

	virtual void HandleInput();

	virtual void HandleOupt();

	virtual void Disconected( int event );
protected:
	CChannelProtocol* m_ChannelProtocol;
	CChannel* m_Channel;
	CSessionCallback* m_SessionCallback;
	unsigned int m_SessionID;

};




#endif