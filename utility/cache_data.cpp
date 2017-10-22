#include "cache_data.h"

bool CCacheData::WriteData(void* data,size_t length)
{
    return true;
}
bool CCacheData::ReadData(size_t id, void* data, long long& length)
{
    return true;
}
bool CCacheData::WriteHead(string headinfo)
{
    return true;
}
bool CCacheData::ReadHead(string& headinfo)
{

    return true;
}