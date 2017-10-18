/************************************************************************/
/* 
用于读取与写入文件
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

class CFileData
{
public:
	CFileData(string filename);
	void WriteData(void* data,size_t length);
	void ReadData(size_t id, void* data, size_t& length);

private:
	FILE* m_file;
	fpos_t m_filePos;
	
};

#endif // !FILEDATA_H
