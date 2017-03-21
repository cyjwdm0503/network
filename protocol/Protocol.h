#ifndef PROTOCOL_H
#define PROTOCOL_H
/************************************************************************/
/* 
发送数据经历protocol的过程为
contentprotocol.Push()->channelprotocol.Push();

或者
contentprotocol.Send()->channelprotocol.Push();

对应的vilidpackage包的流程为
channelpackage.ValidPackage()->contentpackage.ValidPackage()
对应makepackage的流程为：
contentpackage.MakePackage()->channelpackage.MakePackage()
*/
/************************************************************************/
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

/************************************************************************/
/* 继承与CHandler是为了给CChannelProtocol进行输入输出操作                */
/************************************************************************/
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
	//不是为channelprotocol，或者contentprotocol准备的,是上层向contentprotocol进行发送时使用。
	//因为send，不是包引用。而是直接发送包，不包含封装新头部的过程。所以为顶层的protocol(自身发送数据包调用)。Push为响应上层使用。
	//或者contentprotocol直接发送本层的数据包才使用(自身发送数据包调用)。
	virtual int send(CPackage* package);

	virtual int GetReserverLen() const;

	virtual unsigned int GetActiveID();

	/************************************************************************/
	/* CChannelprotocol是没有对应handlePackage的，是为上层协议处理而设定的        
	因此CChaneelProtocol在HandleInput时已经Pop，发往上层协议.上层协议利用HandlePackage再进行上层的Pop*/
	/************************************************************************/
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
