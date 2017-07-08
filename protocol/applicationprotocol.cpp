#include "applicationprotocol.h"
#include "applicationpackage.h"
 

CApplicationProtocol::CApplicationProtocol( CDispatcher* dispatcher):CProtocol(dispatcher,new CApplicationPackage(),new CApplicationPackage(),APPLICATIONHEADERLENGTH)
{
	SetActiveID(1001);
}

CApplicationProtocol::~CApplicationProtocol()
{

}

int CApplicationProtocol::Pop()
{
	return 0;
}
