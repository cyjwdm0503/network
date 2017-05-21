#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <cstring>
#include <cstdlib>
#include <cstdio>

class CBaseStringType
{
};

class CBaseIntTpye 
{
};

class CBaseDoubleType
{

};
class CBaseCharType
{

};

class CBaseShortType
{

};


///����һ����С�ĸ������������Ӧ����Ӱ����������ִ��ڸ��ม��������
#define SMALL_DOUBLE 0.0000001


template <int length> class CStringType: public CBaseStringType
{
public:
	///���캯��
	CStringType(void)
	{
		//buffer[0] = '\0';
	}

	///���ƹ�����
	///@param	s	�����Դ����
	CStringType(const CStringType<length>& s)
	{
		setValue(s.getValue());
	}

	///���ƹ�����
	///@param	p	�����Դ����
	CStringType(const char *p)
	{
		setValue(p);
	}

	///���ڲ�����
	///@param	s	���ڵ�ֵ
	///@return	�����ֵ
	const CStringType & operator =(const CStringType<length>& s)
	{
		setValue(s.getValue());
		return s;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	p	���ڵ��ַ���
	///@return	������ַ���
	const char * operator =(const char *p)
	{
		setValue(p);
		return p;
	}

	///���ڲ��������������л�ȡ
	///@param	v	���ڵ�����
	///@return	���������
	const int operator =(const int v)
	{
		char tmp[100];
		sprintf(tmp,"%*d",length,v);
		setValue(tmp);
		return v;
	}

	///����ַ�������
	void clear(void)
	{
		buffer[0]='\0';
	}

	///��ȡ�ַ�����ֵ
	///@return	�ַ�����ֵ
	const char *getValue(void) const
	{
		return buffer;
	}

	///�����ַ�����ֵ
	///@param	s	Ҫ���õ��ַ���
	void setValue(const char *s)
	{
		if (s==NULL)
			buffer[0]='\0';
		else
		{
			strncpy(buffer,s,length);
			buffer[length]='\0';
		}
	}

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			memcpy(strBuf, buffer,length);
			strBuf[length]='\0';
		}	
	}

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		const char *p=buffer;
		while (*p)
		{
			if (*p!=' ')
			{
				return false;
			}
			p++;
		}
		return true;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		return true;
	}

	///ת��Ϊ�ַ���
	///@return	�õ����ַ���
	operator const char *(void) const
	{
		return buffer;
	}

	///���ұߵĿո�ɾ��
	void trimRight(void)
	{
		char *p = buffer+strlen(buffer)-1;
		while (p >= buffer)
		{
			if (*p != ' ')
			{
				break;
			}
			*p = '\0';
			p--;
		}
	}

	///�ж��Ƿ�С��ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator < (const char *r) const
	{
		return strcmp(buffer,r)<0;
	}

	///�ж��Ƿ����ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator > (const char *r) const
	{
		return strcmp(buffer, r)>0;
	}

	///�ж��Ƿ�С�ڵ���ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator <= (const char *r) const
	{
		return strcmp(buffer,r)<=0;
	}

	///�ж��Ƿ���ڵ���ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator >= (const char *r) const
	{
		return strcmp(buffer, r)>=0;
	}

	///�ж��Ƿ����ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator == (const char *r) const
	{
		return strcmp(buffer, r)==0;
	}

	///�ж��Ƿ񲻵���ĳ���ַ���
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator != (const char *r) const
	{
		return strcmp(buffer, r)!=0;
	}
	
	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		const char *str=buffer;
		
		if (*str == '\0')
		{
			return(ret);
		}
		long n = 0x100;
		while (*str)
		{
			unsigned long v = n|(*str);
			n += 0x100;
			int r = (int)((v>>2)^v)&0x0f;
			ret = (ret<<r)|(ret>>(32-r));
			ret &= 0xFFFFFFFFL;
			ret ^= v*v;
			str++;
		}
		return ((ret>>16)^ret);
	}


protected:
	///�洢�ַ�����ֵ
	char buffer[length+1];
};

#define DefineStringType(length,newType)				\
	typedef CStringType<length> C ## newType;			\
	typedef const CStringType<length> CReadOnly ## newType;


template <int length, int precision> class CDoubleType: public CBaseDoubleType
{
public:
	///���캯��
	CDoubleType(void)
	{
		//clear();
	}

	///���ƹ�����
	///@param	f	�����Դ����
	CDoubleType(const CDoubleType& f)
	{
		setValue(f.getValue());
	}

	///���ƹ�����
	///@param	value	�����Դ����
	CDoubleType(const double value)
	{
		setValue(value);
	}

	///���ڲ�����
	///@param	f	���ڵ�ֵ
	///@return	�����ֵ
	const CDoubleType & operator =(const CDoubleType& f)
	{
		setValue(f.getValue());
		return f;
	}

	///���ڲ��������Ӹ������л�ȡ
	///@param	v	���ڵĸ�����
	///@return	������ָ�����
	const double operator =(const double value)
	{
		setValue(value);
		return value;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	v	���ڵ��ַ���
	///@return	������ַ���
	const char * operator = (const char *v)
	{
		if (v[0]=='\0')
		{
			setValue(DBL_MAX);
		}
		else
		{
			setValue((double)atof(v));
		}
		return v;
	}

	///������ݣ����ǽ�ֵ��Ϊ0
	void clear(void)
	{
		value=0.0;
	}

	///��ȡֵ
	///@return	��ȡ��ֵ
	const double getValue(void) const
	{
		return value;
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	void setValue(const double v)
	{
		if ((v<SMALL_DOUBLE)&&(v>-SMALL_DOUBLE))
		{
			///������Ϊ�˷�ֹ����-0.00000�����������ĳЩ������������ڼ�������-31.0+31.0ʱ���õ��Ľ����-0.0������0.0
			value=0.0;
		}
		else
		{
			value=v;
		}
	}

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			if (value==DBL_MAX)
			{
				strcpy(strBuf,"");
			}
			else
			{
				sprintf(strBuf,"%.5f", value);
			}
		}	
	}	

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		if (value==DBL_MAX)
			return true;
		else
			return false;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		if (value==DBL_MAX)
			return true;
		else if (value>=pow((double) 10,length-precision-1))
			return false;
		else if (value<=-pow((double) 10,length-precision-2))
			return false;
		return true;
	}

	///ת��Ϊʵ��
	///@return	�õ���ʵ��
	operator const double (void) const
	{
		return value;
	}
	
	///����ĳ��ֵ
	///@param	v	Ҫ�ӵ�ֵ
	///@return	�����Ժ�Ľ��
	const double operator += (const double v)
	{
		setValue(value+v);
		return v;
	}

	///��ȥĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�����Ժ�Ľ��
	const double operator -= (double v)
	{
		setValue(value-v);
		return v;
	}

	///����ĳ��ֵ
	///@param	v	Ҫ�˵�ֵ
	///@return	�����Ժ�Ľ��
	const double operator *= (const double v)
	{
		setValue(value*v);
		return v;
	}

	///����ĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�����Ժ�Ľ��
	const double operator /= (const double v)
	{
		setValue(value/v);
		return v;
	}
	
	///����ĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�����Ժ�Ľ��
	const int operator &(const double v) const
	{
		
		return (int)(floor(value/v+SMALL_DOUBLE));
	}

	///�ж��Ƿ�С��ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator < (double r) const
	{
		return value < r-SMALL_DOUBLE;
	}

	///�ж��Ƿ����ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator > (double r) const
	{
		return value > r+SMALL_DOUBLE;
	}

	///�ж��Ƿ�С�ڵ���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator <= (double r) const
	{
		return value <= r+SMALL_DOUBLE;
	}

	///�ж��Ƿ���ڵ���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator >= (double r) const
	{
		return value >= r-SMALL_DOUBLE;
	}

	///�ж��Ƿ����ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator == (double r) const
	{
		return fabs(value-r)<=SMALL_DOUBLE;
	}

	///�ж��Ƿ񲻵���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator != (double r) const
	{
		return fabs(value-r)>SMALL_DOUBLE;
	}

	///�ж��Ƿ�С��ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator < (int r) const
	{
		return value < r-SMALL_DOUBLE;
	}

	///�ж��Ƿ����ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator > (int r) const
	{
		return value > r+SMALL_DOUBLE;
	}

	///�ж��Ƿ�С�ڵ���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator <= (int r) const
	{
		return value <= r+SMALL_DOUBLE;
	}

	///�ж��Ƿ���ڵ���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator >= (int r) const
	{
		return value >= r-SMALL_DOUBLE;
	}

	///�ж��Ƿ����ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator == (int r) const
	{
		return fabs(value-r)<=SMALL_DOUBLE;
	}

	///�ж��Ƿ񲻵���ĳ��ֵ
	///@param	r	�ұ���
	///@return	true��ʾ�ǣ�false��ʾ��
	bool operator != (int r) const
	{
		return fabs(value-r)>SMALL_DOUBLE;
	}

	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		const char *str=(char *)&value;
		int i;
		
		long n = 0x100;
		for (i=0;i<sizeof(double);i++)
		{
			unsigned long v = n|(*str);
			n += 0x100;
			int r = (int)((v>>2)^v)&0x0f;
			ret = (ret<<r)|(ret>>(32-r));
			ret &= 0xFFFFFFFFL;
			ret ^= v*v;
			str++;
		}
		return ((ret>>16)^ret);
	}

protected:
	///�洢��������ֵ
	double value;
};

#define DefineFloatType(maxValue,minValue,newType)			\
	typedef CDoubleType<maxValue,minValue> C ## newType;	\
	typedef const CDoubleType<maxValue,minValue> CReadOnly ## newType;

 
class CIntType: public CBaseIntTpye
{
public:
	///���캯��
	CIntType(void)
	{
		//clear();
	}

	///���ƹ�����
	///@param	i	�����Դ����
	CIntType(const CIntType& i)
	{
		setValue(i.getValue());
	}

	///���ƹ�����
	///@param	i	�����Դ����
	CIntType(const int i)
	{
		setValue(i);
	}

	///���ڲ�����
	///@param	i	���ڵ�ֵ
	///@return	�����ֵ
	const CIntType & operator =(const CIntType& i)
	{
		setValue(i.getValue());
		return i;
	}

	///���ڲ��������������л�ȡ
	///@param	i	���ڵ�����
	///@return	���������
	const int operator =(const int i)
	{
		setValue(i);
		return i;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	v	���ڵ��ַ���
	///@return	������ַ���
	const char * operator =(const char *v)
	{
		setValue(atoi(v));
		return v;
	}

	///������ݣ����ǽ�ֵ��Ϊ0
	void clear(void)
	{
		value=0;
	}
	
	///��ȡֵ
	///@return	��ȡ��ֵ
	const int getValue(void) const
	{
		return value;
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	void setValue(const int v)
	{
		value=v;
	}

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%d", value);
		}	
	}	

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		return false;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		return true;
	}

	///ת��Ϊ����
	///@return	�õ�������
	operator const int (void) const
	{
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ�ӵ�ֵ
	///@return	�õ���ֵ
	const int operator += (const int v)
	{
		setValue(value+v);
		return value;
	}
	
	///�������ȥĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�õ���ֵ
	const int operator -= (const int v)
	{
		setValue(value-v);
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ�˵�ֵ
	///@return	�õ���ֵ
	const int operator *= (const int v)
	{
		setValue(value*v);
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�õ���ֵ
	const int operator /= (const int v)
	{
		setValue(value/v);
		return value;
	}

	///������ģĳ��ֵ
	///@param	v	Ҫģ��ֵ
	///@return	�õ���ֵ
	const int operator %= (const int v)
	{
		setValue(value%v);
		return value;
	}

	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		unsigned  long v = 0x100 | value;
		int r = (int)((v>>2)^v)&0x0f;
		ret = (ret<<r)|(ret>>(32-r));
		ret &= 0xFFFFFFFFL;
		ret ^= v*v;
		return ((ret>>16)^ret);
	}

protected:
	///�洢������ֵ
	int value;
};

typedef const CIntType CReadOnlyIntType;


template <int from, int to> class CRangeIntType: public CBaseIntTpye
{
public:
	///���캯��
	CRangeIntType(void)
	{
		//clear();
	}

	///���ƹ�����
	///@param	i	�����Դ����
	CRangeIntType(const CRangeIntType<from,to>& i)
	{
		setValue(i.getValue());
	}

	///���ƹ�����
	///@param	i	�����Դ����
	CRangeIntType(const int i)
	{
		setValue(i);
	}

	///���ڲ�����
	///@param	i	���ڵ�ֵ
	///@return	�����ֵ
	const CRangeIntType<from,to> & operator =(const CRangeIntType<from,to>& i)
	{
		setValue(i.getValue());
		return i;
	}

	///���ڲ��������������л�ȡ
	///@param	i	���ڵ�����
	///@return	���������
	const int operator =(const int i)
	{
		setValue(i);
		return i;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	v	���ڵ��ַ���
	///@return	������ַ���
	const char * operator =(const char *v)
	{
		setValue(atoi(v));
		return v;
	}

	///������ݣ����ǽ�ֵ��Ϊfrom
	void clear(void)
	{
		value=from;
	}

	///��ȡֵ
	///@return	��ȡ��ֵ
	const int getValue(void) const
	{
		return value;
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	///@exception	CRuntimeError	������ֵԽ�磬���׳����쳣
	void setValue(const int v)
	{
		/*
		if ((v>to)||(v<from))
		{
			RAISE_RUNTIME_WARNING("out of range");
		}
		*/
		value=v;
	}

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%d", value);
		}	
	}

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		return false;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		if ((value>to)||(value<from))
			return false;
		else
			return true;
	}

	///ת��Ϊ����
	///@return	�õ�������
	operator const int (void) const
	{
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ�ӵ�ֵ
	///@return	�õ���ֵ
	const int operator += (const int v)
	{
		setValue(value+v);
		return value;
	}
	
	///�������ȥĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�õ���ֵ
	const int operator -= (const int v)
	{
		setValue(value-v);
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ�˵�ֵ
	///@return	�õ���ֵ
	const int operator *= (const int v)
	{
		setValue(value*v);
		return value;
	}

	///���������ĳ��ֵ
	///@param	v	Ҫ����ֵ
	///@return	�õ���ֵ
	const int operator /= (const int v)
	{
		setValue(value/v);
		return value;
	}

	///������ģĳ��ֵ
	///@param	v	Ҫģ��ֵ
	///@return	�õ���ֵ
	const int operator %= (const int v)
	{
		setValue(value%v);
		return value;
	}

	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		unsigned  long v = 0x100 | value;
		int r = (int)((v>>2)^v)&0x0f;
		ret = (ret<<r)|(ret>>(32-r));
		ret &= 0xFFFFFFFFL;
		ret ^= v*v;
		return ((ret>>16)^ret);
	}
protected:
	///�洢������ֵ
	int value;
};

#define DefineRangeIntType(from,to,newType)					\
	typedef CRangeIntType<from,to> C ## newType;			\
	typedef const CRangeIntType<from,to> CReadOnly ## newType;


class CCharType: public CBaseCharType
{
public:
	///���캯��
	CCharType(void)
	{
		//clear();
	}

	///���ƹ�����
	///@param	c	�����Դ����
	CCharType(const CCharType& c)
	{
		setValue(c.getValue());
	}

	///���ƹ�����
	///@param	c	�����Դ����
	CCharType(const char c)
	{
		setValue(c);
	}

	///���ڲ�����
	///@param	c	���ڵ�ֵ
	///@return	�����ֵ
	const CCharType & operator =(const CCharType& c)
	{
		setValue(c.getValue());
		return c;
	}

	///���ڲ����������ַ��л�ȡ
	///@param	c	���ڵ��ַ�
	///@return	������ַ�
	const char operator =(const char c)
	{
		setValue(c);
		return c;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	v	���ڵ��ַ���
	///@return	������ַ���
	const char * operator =(const char *v)
	{
		setValue(*v);
		return v;
	}

	///������ݣ����ǽ�ֵ��Ϊ'\0'
	void clear(void)
	{
		value='\0';
	}
	
	///��ȡֵ
	///@return	��ȡ��ֵ
	char getValue(void) const
	{
		return value;
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	void setValue(const char v)
	{
		value=v;
	}

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%c", value);
		}	
	}	

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		return false;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		return true;
	}

	///ת��Ϊ�ַ�
	///@return	�õ����ַ�
	operator const char (void) const
	{
		return value;
	}

	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		unsigned  long v = 0x100 | value;
		int r = (int)((v>>2)^v)&0x0f;
		ret = (ret<<r)|(ret>>(32-r));
		ret &= 0xFFFFFFFFL;
		ret ^= v*v;
		return ((ret>>16)^ret);
	}
protected:
	///�洢�ַ���ֵ
	char value;
};

typedef const CCharType CReadOnlyCharType;

#define EnumNull ' '

///���ڶ���һ�����м����ַ�����
///@param	typename	Ҫ���������
///@param	validString	��������ȡֵ���ַ����ɵ��ַ���
#define DefineEnumCharType(typename,validString)				\
	class C ## typename: public CCharType						\
	{															\
	public:														\
		C ## typename(void)										\
		{														\
		}														\
		C ## typename(const C ## typename &v)					\
		{														\
			setValue(v.getValue());								\
		}														\
		C ## typename(const char v)								\
		{														\
			setValue(v);										\
		}														\
		C ## typename(const CCharType &v)						\
		{														\
			setValue(v.getValue());								\
		}														\
		C ## typename& operator=(const C ## typename &c)		\
		{														\
			setValue(c.getValue());								\
			return *this;										\
		}														\
		C ## typename& operator=(const CCharType &c)			\
		{														\
			setValue(c.getValue());								\
			return *this;										\
		}														\
		const char operator =(const char c)						\
		{														\
			setValue(c);										\
			return c;											\
		}														\
		const char * operator =(const char *v)					\
		{														\
			setValue(*v);										\
			return v;											\
		}														\
		void clear(void)										\
		{														\
			setValue(validString[0]);							\
		}														\
		void setValue(const char v)								\
		{														\
/*			if ((v!=EnumNull)&&!strchr(validString,v))			\
			{													\
				RAISE_RUNTIME_WARNING("out of enum char range");\
			}													\
*/			value=v;											\
		} 														\
		bool isNull(void) const									\
		{														\
			return value==EnumNull;								\
		}														\
		bool isValid(void) const								\
		{														\
			if (value=='\0')									\
				return false;									\
			if (strchr(validString,value))						\
				return true;									\
			else												\
				return false;									\
		} 														\
		static bool isValid(const char ch)						\
		{														\
			if (strchr(validString,ch))							\
				return true;									\
			else												\
				return false;									\
		}														\
	};															\
	typedef const C ## typename CReadOnly ## typename;			


typedef  unsigned short WORD ;

class CWordType : public CBaseShortType
{
public:
	///���캯��
	CWordType(void)
	{
//		clear();
	}

	///���ƹ�����
	///@param	w	�����Դ����
	CWordType(const CWordType& w)
	{
		setValue(w.getValue());
	}

	///���ƹ�����
	///@param	w	�����Դ����
	CWordType(WORD w)
	{
		setValue(w);
	}
	
	///���ڲ�����
	///@param	w	���ڵ�ֵ
	///@return	�����ֵ
	const CWordType & operator =(const CWordType& w)
	{
		setValue(w.getValue());
		return w;
	}

	///���ڲ������������л�ȡ
	///@param	w	���ڵ���
	///@return	�������
	const WORD operator =(const WORD w)
	{
		setValue(w);
		return w;
	}

	///���ڲ����������ַ����л�ȡ
	///@param	v	���ڵ��ַ���
	///@return	������ַ���
	const char * operator =(const char *v)
	{
		setValue(atoi(v));
		return v;
	}

	///������ݣ����ǽ�ֵ��Ϊ0
	void clear(void)
	{
		value=0;
	}

	///��ȡֵ
	///@return	��ȡ��ֵ
	WORD getValue(void) const
	{
		return value;
	}

	///����ֵ
	///@param	v	Ҫ���õ�ֵ
	void setValue(WORD v)
	{
		value=v;
	}

	///��strBuf�еõ������͵��ַ�����ʾ	
	///@param	strBuf	���ڷ��ý�����ַ���
	void getString(char *strBuf) const
	{
		if (strBuf!=NULL)
		{
			sprintf(strBuf,"%d", value);
		}	
	}	

	///�ж��Ƿ�Ϊ��
	///@return	true��ʾΪ�գ�false��ʾ��Ϊ��
	bool isNull(void) const
	{
		return false;
	}

	///�ж��Ƿ�Ϸ�
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	bool isValid(void) const
	{
		return true;
	}

	///ת��Ϊ��
	///@return	�õ�����
	operator const WORD (void)
	{
		return value;
	}

	///����hashֵ
	///@param	seed	����
	///@return	�õ���hashֵ
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret=seed;
		unsigned  long v = 0x100 | value;
		int r = (int)((v>>2)^v)&0x0f;
		ret = (ret<<r)|(ret>>(32-r));
		ret &= 0xFFFFFFFFL;
		ret ^= v*v;
		return ((ret>>16)^ret);
	}
protected:
	///�洢�ַ���ֵ
	WORD value;
};

typedef const CWordType CReadOnlyUFWordType;


#define DefineType(pureType, newType)			\
	typedef C ## pureType C ## newType;			\
	typedef CReadOnly ## pureType CReadOnly ## newType;	

#endif