#include "Package.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "Log.h"



CPackageBuffer::CPackageBuffer( int length )
{
	m_pData = new char[length];
	m_bReleaseData = true;
	m_length = length;
	m_nRefCount = 1;
}

CPackageBuffer::CPackageBuffer( char* pData,int length )
{
	m_pData = pData;
	m_length = length;
	m_bReleaseData = false;
	m_nRefCount = 1;
}

CPackageBuffer::~CPackageBuffer()
{
	if(m_bReleaseData == true)
	{
		delete []  m_pData;
		m_pData =  NULL;
	}
}

char* CPackageBuffer::Data()
{
	return m_pData;
}

int CPackageBuffer::Length()
{
	return m_length;
}

void CPackageBuffer::AddRef()
{
	m_nRefCount++;
}

void CPackageBuffer::Release()
{
	if( --m_nRefCount <= 0 )
		delete this;
}

CPackage::CPackage()
{
	m_end = NULL;
	m_head = NULL;
	m_pPackageBuf = NULL;
	m_RefCount = 1;
}

CPackage::~CPackage()
{
	BufRelease();
	//Release();
}
void CPackage::Release()
{
	if(m_RefCount <= 1)
	{
		delete this;
	}
}
void CPackage::Clear()
{
	if(m_pPackageBuf == NULL)
	{
		m_head =  m_end =  NULL;
	}
	else
	{
		m_head = m_pPackageBuf->Data()+m_pPackageBuf->Length();
		m_end = m_head;
	}
}

int CPackage::GetActiveID()
{
	return 0;
}

int CPackage::ValidPackage()
{
	return Length();
}

int CPackage::MakePackage()
{
	return 0;
}

char* CPackage::Push( int size )
{
	if(size <=0)
		return NULL;
	if((m_head-size)>= m_pPackageBuf->Data())
	{
		m_head -=size;
		return m_head;
	}
	return NULL;
}

char* CPackage::Pop( int size )
{
	if(Length()<size)
		return NULL;
	char* tmp = m_head;
	m_head+=size;
	return tmp;
}

int CPackage::Length()
{
	return m_end- m_head;
}

char* CPackage::Address()
{
	return m_head;
}

void CPackage::AddBuf( CPackage* pPackage )
{
	BufRelease();
	m_head =  pPackage->m_head;
	m_end = pPackage->m_end;
	m_pPackageBuf = pPackage->m_pPackageBuf;	
	m_pPackageBuf->AddRef();
}

bool CPackage::CopyPackage( CPackage* pPackage )
{
	AllocMax();
	if(pPackage->Length() > m_pPackageBuf->Length())
		return false;
	memcpy(Address(),pPackage->Address(),pPackage->Length());
	Truncate(pPackage->Length());
	return true;
}

void CPackage::ConstructAlloc( int Capacity, int Reserve )
{
	delete m_pPackageBuf;
	m_pPackageBuf = new CPackageBuffer(Capacity+Reserve);
	m_Reserve = Reserve;
	Clear();//设置首尾节点在末位
}

char* CPackage::AllocMax()
{
	if(m_pPackageBuf == NULL)
		return NULL;
	m_head = m_pPackageBuf->Data()+m_Reserve;
	m_end =  m_pPackageBuf->Data()+m_pPackageBuf->Length();
	return m_head;

}

char* CPackage::Alloc( int length )
{
	if(m_pPackageBuf == NULL){
		return NULL;
	}
	if(length>m_pPackageBuf->Length()){
		return NULL;
	}

	m_end=m_pPackageBuf->Data()+m_pPackageBuf->Length();
	m_head=m_end-length;
	return m_head;
}

void CPackage::Truncate( int newLength )
{
	if(newLength < Length())
		m_end =  m_head+newLength;
}



void CPackage::BufRelease()
{
	CPackageBuffer *old=m_pPackageBuf;
	if(m_pPackageBuf!=NULL){
		m_pPackageBuf->Release();
		m_pPackageBuf=NULL;
		m_head=m_end=NULL;
	}
}

bool CPackage::AppendPackage( CPackage* pPackage )
{
	if(m_end+pPackage->Length() > m_pPackageBuf->Data()+m_pPackageBuf->Length())
		return false;
	memcpy(m_end,pPackage->Address(),pPackage->Length());
	m_end +=pPackage->Length();
	return true;
}
