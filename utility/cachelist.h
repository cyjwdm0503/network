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

	CacheNode(int maxsize);
	~CacheNode();
	/************************************************************************/
	/* push  ��Ӧ�����ݡ�������ʼ��ַ                                            */
	/************************************************************************/
	char* push(void* data,int len);

	/************************************************************************/
	/* ���ض�Ӧ���ȵ����ݣ�����ʵ�ʵĳ�����ָ��λ��                              */
	/************************************************************************/
	void* getdata(int& length);

	/************************************************************************/
	/* ������Ӧ���ȵ����ݣ���getdata�����                                      */
	/************************************************************************/
	int pop(int length);
	//ʣ�¿��Է����ݵĳ���
	int avablesize();
	//ʣ��δpop�����ݳ���
	int size();

private:


	//
	void clear();
public:
	/************************************************************************/
	/* �ڳ���pushǰ���á�                                                                     */
	/************************************************************************/
	bool isdeleted();
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
