#include "Vector.h"


template<typename T>
 Vector<T>::Vector(int size)
{
	 if (size < 0)
	 {
		 throw errNegativeException(size);
	 }
	 else if (size > 100)
	 {
		 throw errToolBigException(size);
	 }
	 else if (size == 0)
	 {
		 throw errZeroException(size);
	 }
	 else if (size < 10)
	 {
		 throw errTooSmallException(size);
	 }
	if (size > 0)
	{
		m_len = size;
		m_base = new T[size];
	}
}

template<typename T>
 Vector<T>::Vector(const Vector<T>& object)
{
	
	 this->m_len = object.m_len;
	 this->m_base = new T[m_len];
	 for (int i = 0; i < m_len; i++)
	 {
		 m_base[i] = object.m_base[i];
	 }
}

 template<typename T>
 int Vector<T>::getLength()
 {
	 return m_len;
 }

 template<typename T>
 T& Vector<T>::operator[](int index)
{
	 return m_base[index];
	// TODO: 在此处插入 return 语句
}

 template<typename T>
 Vector<T>& Vector<T>::operator=(const Vector<T>& object)
 {
	 if (m_base != NULL)
	 {
		 delete[] m_base;
		 m_base = NULL;
		 m_len = 0;
	 }
	 this->m_len = object.m_len;
	 this->m_base = new T[m_len];
	 for (int i = 0; i < m_len; i++)
	 {
		 m_base[i] = object.m_base[i];
	 }
	 return *this;
 }

 template<typename T>
 Vector<T>::~Vector()
 {
	 if (m_base != NULL)
	 {
		 delete[] m_base;
		 m_base = NULL;
		 m_len = 0;
	 }
 }

 //template<typename T>
 // ostream& operator<<(ostream& os, Vector<T>& object)
 //{
	// for (int i = 0; i < object.m_len; i++)
	// {
	//	 os << object.m_base[i] << " ";
	// }
	// os << endl;
	// return os;
 //}
