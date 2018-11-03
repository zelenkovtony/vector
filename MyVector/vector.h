#pragma once
#include <cassert>
/*
TODO list:

���������� ���������� iterator:
	-��� ������� ���������(���������� ���������)
	+��������� ����������� ����������� (�����������)

���������� ���������� vector:
	- ��� ������� ��������� (���������� ������ ��������, � �� ���������)
    + (������ �� ������� � ������������� ��������, �������� ����� ���������)

������ ��� �������:
	+ ����������� pop_back
	+ front � back
	+ capacity(���������� ��������� ����� �� ������ ������)
	- ���������� ������� erase ��� �������� ��������� � ��� ������ �������

������ ��� ����������:
	- ���������� ������ � ������� assert(?) �������� ������ ��������, ����� ��������

~��������� ���-�� ���������~
*/

template <class Type>
class vector{
	size_t m_size;
	Type* m_pData;
	size_t m_nUsed;
	void destroy();
	bool operator==(Type&);
public:
	class iterator;
	vector(size_t = 10);
	vector(const vector&);
	vector(vector&&);
	~vector();
	vector &operator=(const vector&);
	vector &operator=(vector&&);
	void resize();
	void push_back(Type);
	void pop_back(); // ��� ��������� ���������� �������� � �������
	Type& front();
	Type& back();
	size_t size();
	bool empty() const;
	void clear();
	void erase(iterator&);
	void erase(iterator&, iterator&);
	void erase();
	size_t capacity();

	size_t max_size();
	Type &operator[](const size_t&); //������ � �������� ������� �� �������
	iterator begin() const;
	iterator end() const;
};

template <class Type>
class vector<Type>::iterator
{
	Type *m_Data;
	friend vector;
public:
	iterator() {}
	iterator(Type*);
	iterator &operator=(Type*);
	bool operator!=(const iterator&);
	bool operator==(const iterator&);
	iterator &operator++();
	iterator operator++(int);
	iterator &operator--();
	iterator operator--(int);
	Type operator*();
};

template<class Type>
inline void vector<Type>::destroy()
{
	if (m_nUsed)
		delete[] m_pData;
}

template<class Type>
inline vector<Type>::vector(size_t _size) :
	m_size(_size), m_nUsed(0)
{
	m_pData = new Type[m_size];
}

template<class Type>
inline vector<Type>::vector(const vector & _other)
{
	m_size = _other.m_size;
	m_pData = new Type[m_size];
	m_nUsed = _other.m_nUsed;

	for (size_t i = 0; i < m_nUsed; i++)
		m_pData[i] = _other.m_pData[i];

	return *this;

}
template<class Type>
inline vector<Type>::vector(vector && _other):
	m_pData(_other.m_pData), m_size(_other.m_size),
	m_nUsed(_other.m_nUsed)
{
	_other.destroy();
	_other.m_size = 0;
	_other.m_nUsed = 0;
}

template<class Type>
inline vector<Type> & vector<Type>::operator=(const vector &_other)
{
	m_size = _other.m_size;
	m_pData = new Type[m_size];
	m_nUsed = _other.m_nUsed;

	for (size_t i = 0; i < m_nUsed; i++)
		m_pData[i] = _other.m_pData[i];
	return *this;
}

template<class Type>
inline vector<Type> & vector<Type>::operator=(vector &&_other)
{
	m_pData = _other.m_pData;
	m_size = _other.m_size;
	m_nUsed = _other.m_nUsed;

	_other.destroy();
	_other.m_nUsed = 0;
	_other.m_size = 0;
	return *this;
}

template<class Type>
inline vector<Type>::~vector()
{
	destroy();
}

template<class Type>
inline void vector<Type>::resize()
{
	m_size *= 2;
	Type* m_newData = new Type[m_size];

	for (size_t i = 0; i < m_nUsed; i++) {
		m_newData[i] = m_pData[i];
	}

	destroy();
	m_pData = m_newData;
}

template<class Type>
inline void vector<Type>::push_back(Type a)
{
	if (m_nUsed == m_size)
		resize();

	m_pData[m_nUsed++] = a;
}

template<class Type>
inline void vector<Type>::pop_back()
{
	--m_nUsed;
}

template<class Type>
inline Type & vector<Type>::front()
{
	return m_pData[0];
}

template<class Type>
inline Type & vector<Type>::back()
{
	return m_pData[m_nUsed - 1];
}

template<class Type>
inline void vector<Type>::clear()
{
	destroy();
	m_pData = new Type[m_size];
	m_nUsed = 0;
}

template<class Type>
inline void vector<Type>::erase(iterator& _index)
{
	Type* m_newData = new Type[m_size];
	for (size_t i = 0, j = 0; i < m_nUsed; i++) {
		if (m_pData[i] == (*_index.m_Data))
			continue;
		m_newData[j++] = m_pData[i];
		
	}
	m_nUsed--;
	destroy();
	 
	m_pData = m_newData;
}

template<class Type>
inline void vector<Type>::erase(iterator& _first, iterator& _last)
{
	
}

template<class Type>
inline void vector<Type>::erase()
{
	destroy();
	m_nUsed = 0;
	m_pData = new Type[m_size];
}

template<class Type>
inline size_t vector<Type>::capacity()
{
	return m_size-m_nUsed;
}

template<class Type>
inline Type & vector<Type>::operator[](const size_t &_index)
{
	return m_pData[_index];
}

template<class Type>
inline typename vector<Type>::iterator vector<Type>::begin() const
{
	return &m_pData[0];
}

template<class Type>
inline typename vector<Type>::iterator vector<Type>::end() const
{
	return &m_pData[m_nUsed];
}

template<class Type>
inline bool vector<Type>::empty() const
{
	return m_nUsed;
}

template<class Type>
inline size_t vector<Type>::size()
{
	return m_nUsed;
}

template<class Type>
inline vector<Type>::iterator::iterator(Type *_other) :
	m_Data(_other)
{
}

template<class Type>
inline bool vector<Type>::iterator::operator!=(const iterator& _other)
{
	return (*m_Data) != (*_other.m_Data);
}

template<class Type>
inline bool vector<Type>::operator==(Type &_other)
{
	return (*m_pData) == (*_other);
}

template<class Type>
inline bool vector<Type>::iterator::operator==(const iterator& _other)
{
	return *m_Data==*_other.m_Data;
}

template<class Type>
inline typename vector<Type>::iterator & vector<Type>::iterator::operator++()
{
	*m_Data++;
	return *this;
}

template<class Type>
inline typename vector<Type>::iterator & vector<Type>::iterator::operator--()
{
	*m_Data--;
	return *this;
}

template<class Type>
inline Type vector<Type>::iterator::operator*()
{
	return (*m_Data);
}
