#ifndef PACKAGE_H
#define PACKAGE_H

class  CPackageBuffer
{
public:
	CPackageBuffer(int length);
	CPackageBuffer(char* pData,int length);
	virtual ~CPackageBuffer();
	char* Data();
	int Length();
	void AddRef();

	void Release();
private:
	char* m_pData;
	int m_length;
	int m_nRefCount;
	bool m_bReleaseData;
};


///此类的所有分配操作都从位节点往前移动。确定分配的head地址。而不是修改end地址
class CPackage
{
public:
	CPackage();
	virtual ~CPackage();
	virtual void Clear();
	virtual int GetActiveID();
	virtual int ValidPackage();

	//组装对应的package 无错返回0
	virtual int MakePackage();
	//压入多少个字节，返回对应起点的指针。主要是用在头部
	char* Push(int size);
	//弹出size个字节。返回弹出后剩下内容的起点地址。。主要是用在头部
	char* Pop(int size);

	int Length();
	
	//数据的开始地址
	char* Address();
	
	//将其余package引用到当前package。不是复制，只是地址的复制。加了一层引用
	void AddBuf(CPackage* pPackage);
	//复制package
	void CopyPackage(CPackage* pPackage);

	//构造一个package,可用的大小，以及保留的大小，保留的主要是用来以后Push时，可以往前推地址
	void ConstructAlloc(int Capacity, int Reserve);
	//分配最大的空间--与以上搭配使用-与ConstructAlloc搭配用于初始化
	char* AllocMax();
	//在当前的尾部向前申请一串空间，返回起始地址---只能调用一次。与ConstructAlloc搭配使用，用于初始化
	char* Alloc(int length);

	//将尾部进行截断。。从头开始设定长度为newLength 与Alloc类似。只是作用于尾部。。可以多次使用。
	void Truncate(int newLength);

	void Release();

	void BufRelease();

protected:
	CPackageBuffer* m_pPackageBuf;
	char* m_head;
	char* m_end;
	int m_Reserve;
	int m_RefCount;
};



#endif
