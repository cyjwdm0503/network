/************************************************************************/
/* 
目前用于channelprotocol 发送tcp包的缓存管理的list
*/
/************************************************************************/
#ifndef CACHELIST_H
#define CACHELIST_H

#include <list>
#include <string>

class CacheNode
{
public:

	CacheNode(int maxsize):m_maxSize(maxsize)
	{
		m_buf = new char[m_maxSize];
		m_cur =  m_buf;
		m_length = 0;
		m_deleteAll =  false;
	}

	char* push(void* data,int len)
	{
		char* tmp = m_buf+m_length;
		memcpy(tmp,data,len);
		m_length +=len;
		return tmp;
	}

	void* getdata(int& length)
	{
		if(length > size())
			length = size();
		char* ptr =  m_cur;
		return ptr;
	}

	int pop(int length)
	{
		int ret = 0;
		if(size() < length)
		{
			ret = size();
		}
		else
		{
			ret = length;			
		}
		m_cur += ret;
		return ret;

	}
	//剩下未pop的数据长度
	int size()
	{
		return m_length-(m_cur-m_buf);
	}

	//剩下可以放数据的长度
	int avablesize()
	{
		return m_maxSize-size();
	}
	//
	void clear()
	{
		if(size()== 0 && (m_cur-m_buf) == m_length && avablesize() == m_maxSize)
		{	
			delete m_buf;
			m_buf = NULL;
			m_deleteAll = true;
		}
	}
	bool isdeleted()
	{
		return m_deleteAll;
	}
private:
	char* m_buf;
	int m_maxSize;
	char* m_cur;
	int m_length;
	bool m_deleteAll;
};

class CCacheList
{
public:
	CCacheList(int nodesize);
	~CCacheList();
	
	void* get_data(int& length);
	void* push_back(void* data, int length);
	int pop_front(int maxlength);
	bool is_empty();
	void clear();
private:
	typedef std::string CacheNode;
	std::list<CacheNode> m_nodeList;
	int m_nodeSize;

};


#endif