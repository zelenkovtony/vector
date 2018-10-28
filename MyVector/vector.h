#pragma once
#include <cassert>
/*
TODO list:
���������� ���������� iterator
���������� ���������� vector:
- ��� ������� ��������� (���������� ������ ��������, � �� ���������)
- [] (������ �� ������� � ������������� ��������, �������� ����� ���������)
����������� pop_back
������ front � back
����� capacity(���������� ��������� ����� �� ������ ������)
��������� ����������� ����������� ��� ���������(�����������)
���������� ������ � ������� assert(?) �������� ������ ��������, ����� ��������
~��������� ���-�� ���������~
*/
template <class Basic>
class iterator;

template <typename Type>
class vector{
	size_t m_size;
	Type* m_pData;
	size_t m_nUsed;
	friend iterator<Type>;
	void destroy();
	bool operator==(Type&);
public:
	typedef iterator<Type> iterator;
	vector(size_t = 10);
	vector(const vector&);
	vector(vector&&);
	~vector();
	vector &operator=(const vector&);
	vector &operator=(vector&&);
	void resize();
	void push_back(Type);
	void pop_back(Type); // �����������, ��� ��������� ���������� �������� � �������
	iterator begin();
	iterator end();
	size_t size();
	bool empty();
	void clear();
	void erase(iterator);
	size_t max_size();
	Type &operator[](size_t); //������ � �������� ������� �� �������
};

template<class Basic>
class iterator
{
	typedef vector<Basic> vector;
	Basic *m_Data;
	friend vector;
public:
	iterator() {}
	iterator(Basic*);
	iterator &operator=(Basic*);
	bool operator!=(iterator);
	
	bool operator==(iterator);
	bool operator<=(iterator);
	bool operator>=(iterator);
	bool operator<(iterator);
	bool operator>(iterator);
	iterator &operator++();
	iterator operator++(int);
	iterator &operator--();
	iterator operator--(int);
	Basic operator*();
};

template<typename Type>
inline void vector<Type>::destroy()
{
	if (m_nUsed)
		delete[] m_pData;
}

template<typename Type>
inline vector<Type>::vector(size_t _size) :
	m_size(_size), m_nUsed(0)
{
	m_pData = new Type[m_size];
}

template<typename Type>
inline vector<Type>::vector(const vector & _other)
{
	m_size = _other.m_size;
	m_pData = new Type[m_size];

	for (size_t i = 0; i < m_nUsed; i++)
		m_pData[i] = _other.m_pData[i];

	return *this;
}

template<typename Type>
inline vector<Type>::vector(vector && _other):
	m_pData(_other.m_pData), m_size(_other.m_size),
	m_nUsed(_other.m_nUsed)
{
	_other.destroy();
	_other.m_BackIndex = 0;
	_other.m_size = 0;
	_other.m_FrontIndex = 0;
}

template<typename Type>
inline vector<Type> & vector<Type>::operator=(const vector &_other)
{
	m_size = _other.m_size;
	m_pData = new Type[m_size];
	m_nUsed = _other.m_nUsed();

	for (size_t i = 0; i < m_nUsed; i++)
		m_pData[i] = _other.m_pData[i];
	return *this;
}

template<typename Type>
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

template<typename Type>
inline vector<Type>::~vector()
{
	destroy();
}

template<typename Type>
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

template<typename Type>
inline void vector<Type>::push_back(Type a)
{
	if (m_nUsed == m_size)
		resize();

	m_pData[m_nUsed++] = a;
}

template<typename Type>
inline iterator<Type> vector<Type>::begin()
{
	return &m_pData[0];
}

template<typename Type>
inline iterator<Type> vector<Type>::end()
{
	return &m_pData[m_nUsed];
}

template<typename Type>
inline void vector<Type>::clear()
{
	destroy();
	m_pData = new Type[m_size];
	m_nUsed = 0;
}

template<typename Type>
inline void vector<Type>::erase(iterator _index)
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

template<typename Type>
inline size_t vector<Type>::max_size()
{
	return sizeof(Type);
}

template<typename Type>
inline bool vector<Type>::empty()
{
	return m_nUsed;
}

template<typename Type>
inline size_t vector<Type>::size()
{
	return m_nUsed;
}

template<class Basic>
inline iterator<Basic>::iterator(Basic *_other) :
	m_Data(_other)
{
}

template<class Basic>
inline iterator<Basic> & iterator<Basic>::operator=(Basic *_other)
{
	m_Data = _other;
}

template<class Basic>
inline bool iterator<Basic>::operator!=(iterator _other)
{
	return (*m_Data) != (*_other.m_Data);
}

template<typename Type>
inline bool vector<Type>::operator==(Type &_other)
{
	return (*m_pData) == (*_other);
}

template<class Basic>
inline bool iterator<Basic>::operator==(iterator _other)
{
	return *m_Data==*_other.m_Data;
}

template<class Basic>
inline iterator<Basic> & iterator<Basic>::operator--()
{
	*m_Data--;
	return *this;
}

template<class Basic>
inline Basic iterator<Basic>::operator*()
{
	return *m_Data;
}

template<class Basic>
inline iterator<Basic> & iterator<Basic>::operator++()
{
	*m_Data++;
	return *this;
}