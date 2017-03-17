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


///��������з����������λ�ڵ���ǰ�ƶ���ȷ�������head��ַ���������޸�end��ַ
class CPackage
{
public:
	CPackage();
	virtual ~CPackage();
	virtual void Clear();
	virtual int GetActiveID();
	virtual int ValidPackage();

	//��װ��Ӧ��package �޴���0
	virtual int MakePackage();
	//ѹ����ٸ��ֽڣ����ض�Ӧ����ָ�롣��Ҫ������ͷ��
	char* Push(int size);
	//����size���ֽڡ����ص�����ʣ�����ݵ�����ַ������Ҫ������ͷ��
	char* Pop(int size);

	int Length();
	
	//���ݵĿ�ʼ��ַ
	char* Address();
	
	//������package���õ���ǰpackage�����Ǹ��ƣ�ֻ�ǵ�ַ�ĸ��ơ�����һ������
	void AddBuf(CPackage* pPackage);
	//����package
	void CopyPackage(CPackage* pPackage);

	//����һ��package,���õĴ�С���Լ������Ĵ�С����������Ҫ�������Ժ�Pushʱ��������ǰ�Ƶ�ַ
	void ConstructAlloc(int Capacity, int Reserve);
	//�������Ŀռ�--�����ϴ���ʹ��-��ConstructAlloc�������ڳ�ʼ��
	char* AllocMax();
	//�ڵ�ǰ��β����ǰ����һ���ռ䣬������ʼ��ַ---ֻ�ܵ���һ�Ρ���ConstructAlloc����ʹ�ã����ڳ�ʼ��
	char* Alloc(int length);

	//��β�����нضϡ�����ͷ��ʼ�趨����ΪnewLength ��Alloc���ơ�ֻ��������β���������Զ��ʹ�á�
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
