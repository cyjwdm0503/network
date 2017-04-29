#ifndef PROTOCOL_H
#define PROTOCOL_H
/************************************************************************/
/* 
�������ݾ���protocol�Ĺ���Ϊ
contentprotocol.Push()->channelprotocol.Push();

����
contentprotocol.Send()->channelprotocol.Push();

��Ӧ��vilidpackage��������Ϊ
channelpackage.ValidPackage()->contentpackage.ValidPackage()
��Ӧmakepackage������Ϊ��
contentpackage.MakePackage()->channelpackage.MakePackage()

protocolֻ���ṩһ���Ӧ�ķ���package�����package�Ĺ��̡�����������̵�ά����
��session���и���ÿ��session���ƺ�ʱ����protocol���б��ĵķ��͡�
session֮���м̳й�ϵ��
*/
/************************************************************************/
#include "SelectReactor.h"
#include "Package.h"
#include <map>

using namespace std;

class CProtocol;

//������input->Pop���������������ϲ���package���߽�package�Ž�handlepackage���洦�����ߵ����ϲ�Э���Ĭ�Ϸ�ʽhandlepackage���������
//�����������ݼ�����pop���洦��
//
//����Ҫ�ϲ�Э��handlepackage->pop->����handlepackage ����pop��
//����protocol��handlepackage,���������session����handlermessage��

class CProtocolCallback
{
public:
	virtual int HandlePackage(CPackage* pPackage,CProtocol* protocol)= 0;
};

/************************************************************************/
/* �̳���CHandler��Ϊ�˸�CChannelProtocol���������������                */
/************************************************************************/
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
	CProtocol(CDispatcher* reactor,CPackage* pUpperPackage,CPackage* pSendPackage,int ReserverLen);

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

	//�˺������ÿ϶����������и��̶�ʹ�ó�������Ȼ���ܳ���exit;
	//����Ϊchannelprotocol������contentprotocol׼����,���ϲ���contentprotocol���з���ʱʹ�á�
	//��Ϊsend�����ǰ����á�����ֱ�ӷ��Ͱ�����������װ��ͷ���Ĺ��̡�����Ϊ�����protocol(���������ݰ�����)��PushΪ��Ӧ�ϲ�ʹ�á�
	//����contentprotocolֱ�ӷ��ͱ�������ݰ���ʹ��(���������ݰ�����)��
	virtual int send(CPackage* package);

	virtual int GetReserverLen() const;

	virtual unsigned int GetActiveID();

	/************************************************************************/
	/* CChannelprotocol��û�ж�ӦhandlePackage�ģ���Ϊ�ϲ�Э�鴦����趨��        
	���CChaneelProtocol��HandleInputʱ�Ѿ�Pop�������ϲ�Э��.�ϲ�Э������HandlePackage�ٽ����ϲ��Pop*/
	/************************************************************************/
	virtual int HandlePackage(CPackage* pPackage,CProtocol* protocol);

protected:
	//һ��Э���ϲ㲻Ӧ�ô��ڶ��activeIDһ�����ϲ�Э��
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
	//handler һ����protocol��Ӧ��handler��session
	CHandler* m_errHandler;
	CProtocolCallback* m_uppderHandler;

	CPackage* m_upperPackage;
	CPackage* m_sendPackage;
	CProtocol* m_lower;
	//uppermap�����Ƕ�Ӧ��Э��ջ
	map<unsigned int,CProtocol*> m_upperMap;
	int m_reserveLen;
	unsigned int m_activeID;
	

};

#endif // !PROTOCOL_H
