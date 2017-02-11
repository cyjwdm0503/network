#include "channelpackage.h"
#include "Log.h"

 

bool CChannelPackage::PopPackage( CPackage* package )
{
	if( GetDataLen() < sizeof(header))
		return false;

	header head;
	memcpy(&head,cur,sizeof(header));

	if(GetDataLen()< head.PACKAGELENGTH)
		return false;

	memcpy(package->GetPackagePtr(),cur,head.PACKAGELENGTH);
	cur +=head.PACKAGELENGTH;
	//pop完成后，要将后来的值移动到begin位置
	memmove(begin,cur,end-cur);
	end -= head.PACKAGELENGTH;
	cur -= head.PACKAGELENGTH;
	return true;
}

void CChannelPackage::MakePackage()
{
	;
}

int CChannelPackage::ReadFromChannel( CChannel* channel )
{
	int ret = channel->Read(GetValidLength(),GetValidDataPtr());
	if(ret <=0)
	{
		CLog::GetInstance()->Printerrno(ret);
		channel->Disconnect();
		return ret;
		//exit(1);
	}

	end = end+ret;
	return ret;
}

CChannelPackage::CChannelPackage( unsigned int PACKAGEID,int maxlen/*=1024*/ ):CPackage(CHANNELPACKAGE_ID,maxlen)
{
	end = begin;
}

 
