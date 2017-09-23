#include "applicationprotocol.h"
#include "applicationpackage.h"
 

CApplicationProtocol::CApplicationProtocol( CDispatcher* dispatcher):CProtocol(dispatcher,new CApplicationPackage(),new CApplicationPackage(),APPLICATIONHEADERLENGTH)
{
	SetActiveID(APPLICATION_ACTIVE_ID);
	m_sendPackage->ConstructAlloc(APPLICATIONPACKAGE_MAXLENGTH,256);
}

CApplicationProtocol::~CApplicationProtocol()
{

}


int CApplicationProtocol::Pop( CPackage* package )
{
	/************************************************************************/
	/*�ڴ˴���Ĭ�ϴ����Ӧ��ҵ���ģ�����һ�������Ķ����аɡ�                                                                     */
	/************************************************************************/
	
	//����applicationprotocol�Ѿ������ϲ�Э�飬��ʱ��pop��Ҫ�ǵ��ö�Ӧ��ProtocolCallback��
	//��˶�Ӧ��session��Ҫ�̳���ProtocolCallback
	m_uppderHandler->HandlePackage(package,this);
	return 0;
}

//Session���ڷ������ݵĽӿڣ���ͨ������ӿڷ���
 int CApplicationProtocol::send(CPackage* pacakge)
{
	m_sendPackage->CopyPackage(pacakge);
	return CProtocol::send(m_sendPackage);
}

