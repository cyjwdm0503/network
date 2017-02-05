#ifndef PACKAGE_H
#define PACKAGE_H

const unsigned int PACKAGE_ID = 1;
const unsigned int CHANNELPACKAGE_ID = 2;

#include "Channel.h"
/************************************************************************/
/* 
*/
/************************************************************************/

typedef struct SPackageHead
{
	 int PACKAGEID;
	 int DATALENGTH;
	 int PACKAGELENGTH;
	 int VERSION;
}header;


class CPackage
{
public:
	CPackage();
	CPackage(unsigned int PACKAGEID,int maxlen=1024);
	virtual ~CPackage();
	//将上层的package写入到当前层
	virtual bool PushPackage(CPackage* package);
	//获取当前package里面存的上层package
	virtual bool PopPackage(CPackage* package);

	//在上层package写入时，push上层package的数据头。以便GetPackage能正确取出上层Package
	void PushHeader();
	bool PopHeader();
	//利用m_data的数据值，组装当前层的Package
	virtual void MakePackage();

	//获取header
	header* GetHeader();

	//获取数据的起始地址
	char* GetDataPtr();
	char* GetPackagePtr();

	//获取数据的长度
	unsigned int GetDataLen() const;
	unsigned int GetPackageLen() const;

	//可以读取的最大数据
	unsigned int GetValidLength() const;

	//用于底层获取指针，读取数据
	char* GetValidDataPtr();

protected:
	


	char* m_data;
	char* begin;
	char* cur;
	char* end;
	unsigned int m_maxlen;
	header m_header; 
};

#endif