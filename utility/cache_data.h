#ifndef UTILITY_DATA_H
#define UTILITY_DATA_H


#include "filedata.h"

class CCacheData:public PackageDataInterface
{
    virtual bool WriteData(void* data,size_t length);
	virtual bool ReadData(size_t id, void* data, long long& length);
	virtual bool WriteHead(string headinfo);
	virtual bool ReadHead(string& headinfo);
};

#endif
