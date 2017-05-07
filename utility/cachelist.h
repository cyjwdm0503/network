/************************************************************************/
/* 
目前用于channelprotocol 发送tcp包的缓存管理的list
*/
/************************************************************************/
#ifndef CACHELIST_H
#define CACHELIST_H

#include <list>
#include <string>
#include <cstring>
const int MAXNODELENGTH = 25;

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
	~CacheNode()
	{
		if(m_buf != NULL)
		{
			delete m_buf;
			m_buf = NULL;
		}
		m_cur =  NULL;
	}
	/************************************************************************/
	/* push  对应的内容。返回起始地址                                            */
	/************************************************************************/
	char* push(void* data,int len)
	{
		char* tmp = m_buf+m_length;
		memcpy(tmp,data,len);
		m_length +=len;
		return tmp;
	}

	/************************************************************************/
	/* 返回对应长度的内容，返回实际的长度与指针位置                              */
	/************************************************************************/
	void* getdata(int& length)
	{
		if(length > size())
			length = size();
		char* ptr =  m_cur;
		return ptr;
	}

	/************************************************************************/
	/* 弹出对应长度的内容，在getdata后调用                                      */
	/************************************************************************/
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
		//在pop后尝试调用clear
		clear();
		return ret;

	}
	//剩下可以放数据的长度
	int avablesize()
	{
		return m_maxSize-size();
	}
	//剩下未pop的数据长度
	int size()
	{
		return m_length-(m_cur-m_buf);
	}

private:


	//
	void clear()
	{
		if(size()== 0 && (m_cur-m_buf) == m_length && avablesize() == m_maxSize)
		{	
			delete m_buf;
			m_buf = NULL;
			m_cur = NULL;
			m_deleteAll = true;
		}
	}
public:
	/************************************************************************/
	/* 在尝试push前调用。                                                                     */
	/************************************************************************/
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
	CCacheList();
	~CCacheList();
	
	void* get_data(int& length);
	void* push_back(void* data, int length);
	int pop_front(int maxlength);
	int is_empty();
private:
	 
	std::list<CacheNode*> m_nodeList;
	int m_nodeSize;

};


#endif
