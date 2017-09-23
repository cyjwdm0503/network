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
	/*在此处来默认处理对应的业务报文，存入一个带锁的队列中吧。                                                                     */
	/************************************************************************/
	
	//由于applicationprotocol已经是最上层协议，此时的pop主要是调用对应的ProtocolCallback。
	//因此对应的session需要继承与ProtocolCallback
	m_uppderHandler->HandlePackage(package,this);
	return 0;
}

//Session用于发送数据的接口，都通过这个接口发送
 int CApplicationProtocol::send(CPackage* pacakge)
{
	m_sendPackage->CopyPackage(pacakge);
	return CProtocol::send(m_sendPackage);
}

