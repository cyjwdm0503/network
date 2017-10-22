#include "filedata.h"

CFileData::CFileData( string filename )
{
	m_dataName = string(filename)+".data";
	m_idName = string(filename)+".id";
	m_dataFile = NULL;
	m_idFile = NULL;
	m_maxID = 0;
	SETFPOS(m_idPos,0);
	SETFPOS(m_dataPos,0);
	OpenFile();
}

CFileData::CFileData()
{
	m_dataName = string("test")+".data";
	m_idName = string("test")+".id";
	m_maxID = 0;
	m_dataFile = NULL;
	m_idFile = NULL;
	SETFPOS(m_idPos,0);
	SETFPOS(m_dataPos,0);
	OpenFile();
}

bool CFileData::WriteData( void* data,size_t length )
{
	CMutexGuard guard(m_mtx);
	if(length >0)
	{
		if(m_idFile  && m_dataFile)
		{
			m_maxID++;
			fsetpos(m_dataFile,&m_dataPos);
			fwrite(data,1,length,m_dataFile);

			DataNode node;
			node.size =  length;
			node.pos = GETFPOS(m_dataPos);

			fsetpos(m_idFile,&m_idPos);
			fwrite(&node,1,sizeof(DataNode),m_idFile);

			fgetpos(m_dataFile,&m_dataPos);
			fgetpos(m_idFile,&m_idPos);
			return true;
		}
		return false;
	}
	return false;
}

bool CFileData::ReadData( size_t id, void* data, long long& length )
{

	CMutexGuard guard(m_mtx);
	if(id > m_maxID)
	{
		length = 0;
		return false;
	}
	else
	{
		DataNode node =  GetDataNode(id);

		fpos_t pos;
		SETFPOS(pos,node.pos);
		fsetpos(m_dataFile,&pos);
		length = fread(data,1,node.size,m_dataFile);
		return true;
	}

}

void CFileData::OpenFile()
{
	m_dataFile =  fopen(m_dataName.c_str(),"w+");
	m_idFile = fopen(m_idName.c_str(),"w+");

}

DataNode CFileData::GetDataNode( size_t id )
{
	DataNode node;
	fpos_t datapos;
	SETFPOS(datapos,0);
	if(id <= m_maxID)
	{
		fpos_t idpos;
		SETFPOS(idpos,DATAHEADLENGTH+id*sizeof(DataNode));
		if(!fsetpos(m_idFile,&idpos))
		{
			
			if(sizeof(DataNode) == fread(&node,1,sizeof(DataNode),m_idFile))
			{
				return node;
			}
		}
	}
	return node;
}

bool CFileData::WriteHead( string headinfo )
{
	if(m_idFile)
	{
		char buf[DATAHEADLENGTH];
		memset(buf,0,sizeof(buf));
		fseek(m_idFile,0,SEEK_SET);
		fwrite(buf,1,sizeof(buf),m_idFile);
		fseek(m_idFile,0,SEEK_SET);
		fwrite(headinfo.c_str(),1,headinfo.length(),m_idFile);
		SETFPOS(m_idPos,DATAHEADLENGTH);
		return true;
	}
	return false;
}

long long  CFileData::GetMaxID()
{
	if(m_maxID != 0)
		return m_maxID;
	if(m_idFile != NULL)
	{
		fpos_t  currPos;
		fpos_t	maxPos;
		if(0 != fgetpos(m_idFile,&currPos))
			return 0;
		if(0 != fseek(m_idFile,0,SEEK_END))
			return 0;
		if(!fgetpos(m_idFile,&maxPos))
		{
			long long  length;
			length = GETFPOS(maxPos);
			if(length-DATAHEADLENGTH>0)
			{
				m_maxID = (length-DATAHEADLENGTH)/sizeof(DataNode);
				fsetpos(m_idFile,&currPos);
				return m_maxID;
			}
		}
	}
	return 0;
}

bool CFileData::ReadHead( string& headinfo )
{
	if(m_idFile != NULL)
	{
		DataHead head;
		fseek(m_idFile,0,SEEK_SET);
		if(DATAHEADLENGTH == fread(head.head,1,DATAHEADLENGTH,m_idFile))
		{
			headinfo = head.head;
			return true;
		}
		else
		{
			headinfo = "";
			return false;
		}
	}
	return false;
}

CFileData::~CFileData()
{
	if(m_idFile)
	{
		fclose(m_idFile);
	}
	if(m_dataFile)
	{
		fclose(m_dataFile);
	}
	m_idFile =  NULL;
	m_dataFile =  NULL;
}
