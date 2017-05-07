/************************************************************************/
/* 
Ŀǰ����channelprotocol ����tcp���Ļ�������list
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
	/* push  ��Ӧ�����ݡ�������ʼ��ַ                                            */
	/************************************************************************/
	char* push(void* data,int len)
	{
		char* tmp = m_buf+m_length;
		memcpy(tmp,data,len);
		m_length +=len;
		return tmp;
	}

	/************************************************************************/
	/* ���ض�Ӧ���ȵ����ݣ�����ʵ�ʵĳ�����ָ��λ��                              */
	/************************************************************************/
	void* getdata(int& length)
	{
		if(length > size())
			length = size();
		char* ptr =  m_cur;
		return ptr;
	}

	/************************************************************************/
	/* ������Ӧ���ȵ����ݣ���getdata�����                                      */
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
		//��pop���Ե���clear
		clear();
		return ret;

	}
	//ʣ�¿��Է����ݵĳ���
	int avablesize()
	{
		return m_maxSize-size();
	}
	//ʣ��δpop�����ݳ���
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
	/* �ڳ���pushǰ���á�                                                                     */
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
