#pragma once

template <class Basic>
class iterator;
template <typename Type>
class vector{
	
	friend iterator<Type>;
	
public:
	size_t m_size;
	Type* m_pData;
	size_t m_nUsed;
	typedef iterator<Type> iterator;

	vector(size_t = 10);
	~vector();
	void resize();
	void push_back(Type);
	void insert();
	void begin();
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

