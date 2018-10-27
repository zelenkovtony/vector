#pragma once

template <class Basic>
class iterator;
template <typename Type>
class vector{
	size_t m_size;
	Type* m_pData;
	size_t m_nUsed;
	friend iterator<Type>;
	
public:

	typedef iterator<Type> iterator;
	vector(size_t = 10);
	~vector();
	void resize();
	void push_back(Type);
	void insert();
	iterator begin();
	iterator end();
	size_t size();
	bool empty();
	
	void clear();
	void erase(iterator );
};
template<class Basic>
class iterator
{
	typedef vector<Basic> vector;
	Basic *m_Data;
public:
	iterator() {}
	iterator(Basic*);
	iterator &operator=(Basic*);
	bool operator!=(iterator);
	bool operator==(Basic&);
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
inline vector<Type>::vector(size_t _size) :
	m_size(_size), m_nUsed(0)
{
	m_pData = new Type[m_size];
}
template<typename Type>
inline vector<Type>::~vector()
{
	delete[] m_pData;
}
template<typename Type>
inline void vector<Type>::resize()
{
	size_t _oldsize = m_size;
	m_size *= 2;
	Type* m_newData = new Type[m_size];
	for (size_t i = 0; i < _oldsize; i++) {
		m_newData[i] = m_pData[i];
	}
	delete [] m_pData;
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
inline void vector<Type>::insert()
{
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
	m_nUsed = 0;
	delete [] m_pData;
	m_pData = new Type[m_size];
	
}

template<typename Type>
inline void vector<Type>::erase(iterator _index)
{
	size_t _oldsize = m_size;
	m_size *= 2;
	Type* m_newData = new Type[m_size];
	for (size_t i = 0; i < _oldsize; i++) {
		if (m_pData[i] == _index.m_Data)
			continue;
		m_newData[i] = m_pData[i];
		
	}
	m_nUsed--;
	delete[] m_pData;
	 
	m_pData = m_newData;
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
inline iterator<Basic>::iterator(Basic *_arr) :
	m_Data(_arr)
{
}
template<class Basic>
inline bool iterator<Basic>::operator==(Basic &_other)
{
	return (*m_Data) == (*_other);
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