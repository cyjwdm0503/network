#include "applicationprotocol.h"
#include "applicationpackage.h"
 

CApplicationProtocol::CApplicationProtocol( CDispatcher* dispatcher):CProtocol(dispatcher,new CApplicationPackage(),new CApplicationPackage(),APPLICATIONHEADERLENGTH)
{
	SetActiveID(1001);
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
	CProtocol::Pop(package);
	return 0;
}
