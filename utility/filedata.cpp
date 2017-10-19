#include "filedata.h"

CFileData::CFileData( string filename )
{
	m_dataname = string(filename)+".data";
	m_idname = string(filename)+".id";
	m_datafile = NULL;
	m_idfile = NULL;
}

void CFileData::WriteData( void* data,size_t length )
{

}

void CFileData::ReadData( size_t id, void* data, size_t& length )
{

}

void CFileData::OpenFile()
{
	m_datafile =  fopen(m_)
}

