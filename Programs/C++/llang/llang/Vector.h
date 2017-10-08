#ifndef _VECTOR
#define _VECTOR

#include <iostream>

template<typename T>
class Vector {
public:
	explicit Vector(void)
		: m_capacity(8),m_size(0)
	{
		m_arrOfValues = new T[m_capacity];
	}
	~Vector(void)
	{
	}
public:
	void M_PushBack(T p_itemToPush) {
		if(m_size == m_capacity) {
			m_capacity *= 2;
			T* l_tempArr = new T[m_capacity];
			for(size_t l_index = 0; l_index < m_size; l_index++) 
				l_tempArr[l_index] = m_arrOfValues[l_index];
			delete[] m_arrOfValues;
			m_arrOfValues = l_tempArr;
		}
		if(m_size < m_capacity) {
			m_arrOfValues[m_size] = p_itemToPush;
			m_size++;
		}
	}
	T& operator[](size_t p_index) const { return m_arrOfValues[p_index]; };
	void operator()(Vector<T> p_otherVec) {
		memcpy(this->m_arrOfValues,p_otherVec.m_arrOfValues,p_otherVec.m_size);
		this->m_size = p_otherVec.m_size;
		this->m_capacity = p_otherVec.m_capacity;
	}
public:
	T* m_arrOfValues;
	size_t m_capacity;
	size_t m_size;
};

#endif