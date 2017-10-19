/************************************************************************/
/* 
用于读取与写入文件
每次存入的数据需要存入对应的报文长度.为了方便快速查找对应id数据，附加一个ID文件，用于记录每100个的位置

*/
/************************************************************************/


#ifndef FILEDATA_H
#define FILEDATA_H


#include <cstdio>
#include <cstring>
#include <string>

using namespace  std ;


//两类系统fpos_t不一致
#ifdef WIN

#ifndef GETFPOS
#define GETFPOS(pos) (pos)
#endif

#ifndef SETFPOS
#define SETFPOS(pos,value)  ((value) = (pos))
#endif

#else

#ifndef GETFPOS
#define GETFPOS(pos) ((pos).__pos)
#endif

#ifndef SETFPOS
#define SETFPOS(pos,value) ((value) = ((pos).__pos))
#endif

#endif

struct DataNode
{
	unsigned long long id;
	size_t			size;
};

class CFileData
{
public:
	CFileData(string dataname);
	void WriteData(void* data,size_t length);
	void ReadData(size_t id, void* data, size_t& length);

private:
	void OpenFile();
	FILE* m_datafile;
	FILE* m_idfile;
	fpos_t m_filePos;
	string m_dataname;
	string m_idname;
	
};

#endif // !FILEDATA_H
