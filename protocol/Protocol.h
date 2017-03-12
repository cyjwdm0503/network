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
	/*���ȵ�ractor
	�ϲ��package
	�����package
	�����ĳ���
	*/
	/************************************************************************/
	CProtocol(CSelectReactor* reactor,CPackage* pUpperPackage,CPackage* pSendPackage,int ReserverLen);

	virtual ~CProtocol();

	/************************************************************************/
	/* �²�Э��
	��ǰ���ID,д���²�Э���headerͷ��������ָ����Ӧ���ϲ�Э��
	*/
	/************************************************************************/
	virtual void AttachLower(CProtocol* pLower);

	virtual void SetActiveID(unsigned int activeid);

	virtual void RegisterUpperHandler(CProtocolCallback* pUpperHandler);

	//�¼�����
	virtual void RegisterErrHandler(CHandler* pHandler);

	virtual int send(CPackage* package);

	virtual int GetReserverLen() const;

	virtual unsigned int GetActiveID();

	virtual int HandlePackage(CPackage* pPackage,CProtocol* protocol);

protected:
	void AddUpper(CProtocol* pUpper);
	
	CProtocol* GetUpper(unsigned int activeid);

	CProtocol* RemoveUpper(unsigned int activeid);

	CProtocol* GetLower();
	
	//���뵱ǰ���package�����ҵ���package��Ӧ���ϴ�Э�顣����handlepackage���е���
	virtual int Pop(CPackage* package);

	virtual int OnRecvErrPackage(CPackage* package);

	void NotifyErr(int msg,unsigned int dwParam, void* pParam);

	virtual int Push(CPackage* package,CProtocol* protocol);

protected:
	CHandler* m_pErrHandler;
	CPackage* m_upperPackage;
	CPackage* m_sendPackage;
	CProtocol* p_lower;
	map<unsigned int,CProtocol*> m_UpperMap;
	int m_reservelen;
	unsigned int m_activeid;
	CProtocolCallback* m_pUppderHandler;

};

#endif // !PROTOCOL_H
