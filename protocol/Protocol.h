#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "SelectReactor.h"
#include "Package.h"
#include <map>

using namespace std;

class CProtocol;
class CProtocolCallback
{
public:
	virtual int HandlePackage(CPackage* pPackage,CProtocol* protocol)= 0;
};

class CProtocol:public CHandler,public CProtocolCallback
{
public:
	/************************************************************************/
	/*调度的ractor
	上层的package
	本层的package
	保留的长度
	*/
	/************************************************************************/
	CProtocol(CSelectReactor* reactor,CPackage* pUpperPackage,CPackage* pSendPackage,int ReserverLen);

	virtual ~CProtocol();

	/************************************************************************/
	/* 下层协议
	当前层的ID,写于下层协议的header头部。用来指定对应的上层协议
	*/
	/************************************************************************/
	virtual void AttachLower(CProtocol* pLower);

	virtual void SetActiveID(unsigned int activeid);

	virtual void RegisterUpperHandler(CProtocolCallback* pUpperHandler);

	//事件对象
	virtual void RegisterErrHandler(CHandler* pHandler);

	//此函数调用肯定是来自于有个固定使用场景，不然不能出现exit;
	virtual int send(CPackage* package);

	virtual int GetReserverLen() const;

	virtual unsigned int GetActiveID();

	virtual int HandlePackage(CPackage* pPackage,CProtocol* protocol);

protected:
	//一个协议上层不应该存在多个activeID一样的上层协议
	void AddUpper(CProtocol* pUpper);
	
	CProtocol* GetUpper(unsigned int activeid);

	CProtocol* RemoveUpper(unsigned int activeid);

	CProtocol* GetLower();
	
	//传入当前层的package，并找到此package对应的上次协议。利用handlepackage进行调用
	virtual int Pop(CPackage* package);

	virtual int OnRecvErrPackage(CPackage* package);

	void NotifyErr(int msg,unsigned int dwParam, void* pParam);

	virtual int Push(CPackage* package,CProtocol* protocol);

protected:
	//handler 一般是protocol对应的handler的session
	CHandler* m_errHandler;
	CProtocolCallback* m_uppderHandler;

	CPackage* m_upperPackage;
	CPackage* m_sendPackage;
	CProtocol* m_lower;
	//uppermap里面是对应的协议栈
	map<unsigned int,CProtocol*> m_upperMap;
	int m_reserveLen;
	unsigned int m_activeID;
	

};

#endif // !PROTOCOL_H
