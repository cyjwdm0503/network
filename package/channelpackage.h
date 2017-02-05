#ifndef CHANNELPACKAGE_H
#define CHANNELPACKAGE_H
#include "Package.h"
class CChannelPackage:public CPackage
{
public:
	CChannelPackage(unsigned int PACKAGEID,int maxlen=1024);
	virtual bool PopPackage( CPackage* package );
	int ReadFromChannel(CChannel* channel);
private:
	virtual void MakePackage();


};
#endif // !CHANNELPACKAGE_H
