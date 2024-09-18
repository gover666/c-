#pragma once
#include<iostream>
using namespace std;
class errSizeException
{
public:
	errSizeException(int size)
	{
		this->size = size;
	}
	virtual void printError()
	{
		cout << "size:" << size << endl;
	}
protected:
	int size;
};
class errNegativeException:public errSizeException
{
public:
	errNegativeException(int size):errSizeException(size)
	{
		this->size = size;
	}
	virtual void printError()
	{
		cout << "errNegativeException size:" <<size<< endl;
	}

};

class errZeroException:public errSizeException
{
public:
	errZeroException(int size) :errSizeException(size)
	{
		this->size = size;
	}
	virtual void printError()
	{
		cout << "errZeroException size:" << size << endl;
	}
};

class errToolBigException:public errSizeException
{
public:
	errToolBigException(int size) :errSizeException(size)
	{
		this->size = size;
	}
	virtual void printError()
	{
		cout << "errToolBigException size:" << size << endl;
	}
};
class errTooSmallException :public errSizeException
{
public:
	errTooSmallException(int size) :errSizeException(size)
	{
		this->size = size;
	}
	virtual void printError()
	{
		cout << "errTooSmallException size:" << size << endl;
	}
};


template<typename T>
class Vector
{
public:
	Vector(int size = 128);//构造函数
	Vector(const Vector& object);//拷贝构造函数


	int getLength();
	T& operator[](int index);
	Vector& operator=(const Vector& object);
	friend ostream& operator<<(ostream& os, Vector& object)
	{
		for (int i = 0; i < object.m_len; i++)
		{
			os << object.m_base[i] << " ";
		}
		os << endl;
		return os;
	}



	~Vector();
protected:
	int m_len;
	T* m_base;
};

//template<typename T>
//ostream& operator<<(ostream& os, Vector<T>& object)
//{
//	for (int i = 0; i < object.m_len; i++)
//	{
//		os << object.m_base[i] << " ";
//	}
//	os << endl;
//	return os;
//}


