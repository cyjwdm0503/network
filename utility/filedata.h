/************************************************************************/
/* 
用于读取与写入文件
每次存入的数据需要存入对应的报文长度.为了方便快速查找对应id数据，附加一个ID文件，用于记录每100个的位置

*/
/************************************************************************/


#ifndef UTILITY_FILEDATA_H
#define UTILITY_FILEDATA_H

#include "MutexGuard.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace  std ;


//两类系统fpos_t不一致
#if defined(WIN) || defined(MAC)

#ifndef GETFPOS
#define GETFPOS(idpos) (idpos)
#endif

#ifndef SETFPOS
#define SETFPOS(idpos,value)  ((idpos) = (value))
#endif

#else

#ifndef GETFPOS
#define GETFPOS(idpos) ((idpos).__pos)
#endif

#ifndef SETFPOS
#define SETFPOS(idpos,value) (((idpos).__pos)=(value))
#endif

#endif

//id文件的头部，用于描述文件基本信息
struct DataHead
{
	char head[1024];
};

//id文件的节点内容----每个Data写一次
struct DataNode
{
	unsigned long long pos;
	size_t size;
	DataNode():pos(0),size(0){}
};


const size_t DATAHEADLENGTH =  sizeof(DataHead);

class CFileData
{
public:
	CFileData(string dataname);
	CFileData();
	~CFileData();
	void WriteData(void* data,size_t length);
	void ReadData(size_t id, void* data, long long& length);
	long long  GetMaxID();
	void WriteHead(string headinfo);
	bool ReadHead(string& headinfo);
private:
	DataNode GetDataNode(size_t id);
	void OpenFile();




	long long  m_maxID;
	FILE* m_dataFile;
	FILE* m_idFile;
	fpos_t m_idPos;
	fpos_t m_dataPos;
	string m_dataName;
	string m_idName;
	CMutex m_mtx;
	
};

#endif // !FILEDATA_H
