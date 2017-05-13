#ifndef APPLICATIONPACKAGE_H 
#define APPLICATIONPACKAGE_H
#include "Package.h"
/************************************************************************/
/* 应用层协议，contentpackage主要是用来确保每个包是一个完整的数据包，但是没法对应于业务。
此package对应于业务，每个package内都是存取的分业务的数据包。
package里面放置field,每次放置field时，在field前放置一个fieldheader，然后复制field内容。
从package取出field的过程是也是通过读取filedheader,然后进行内容复制。
取出数据的过程是通过package获取一个迭代器，进行取出。
存入数据的过程，每次会想package申请一块空间，然后进行存入。
applicationpackage 存入field.field的规则描述为fielddescribe。
*/
/************************************************************************/
struct CFieldHeader
{
	unsigned short FieldID;
	unsigned short FieldLength;
};

class CFieldIterator
{
public:
	CFieldIterator(char* head,char* end,CF);
};

class CFieldSet:public CPackage
{

};

#endif