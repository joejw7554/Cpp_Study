#pragma once

#include "assert.h"
#include "iostream"

using namespace std;
template<typename T>
class CArr
{
private:
	T* m_pData;
	int m_iCount;
	int m_iMaxCount;

public:
	void Resize(int _iResizeCount);
	void PushBack(const T& iData);
	T* data() { return m_pData; }
	int size() { return m_iCount; }
	int capacity() { return m_iMaxCount; }
	T& operator[] (int idx);

	class iterator; //전방 선언 //Innerclass 를 포함한 클래스는 Private 멤버를 접근할 수 있다.
	iterator begin();
	iterator end();
	iterator erase(iterator& iter);
	void clear();

	CArr();
	~CArr();

	class iterator
	{
	private:
		CArr* m_pArr;
		T* m_pData;
		int m_index;
		bool m_bValid;

	public:
		T& operator *()
		{
			if (m_pArr->m_pData != m_pData || -1 == m_index ||!m_bValid) // iter가 end iter거나 알고있는 주소와 가변배열이 알고있는 주소가 다를경우
			{
				assert(nullptr);
			}

			return m_pData[m_index];
		}

		//전위
		iterator& operator ++()
		{
			//2. end iterator 인 경우
				//end iter 에서 증가할 경우 예외처리
				// iter가 end iter거나 알고있는 주수와 가변배열이 알고있는 주소가 다를경우
			if (m_pArr->m_pData != m_pData || -1 == m_index) // iter가 end iter거나 알고있는 주소와 가변배열이 알고있는 주소가 다를경우
			{
				assert(nullptr);
			}

			//1. iterator 가 마지막 데이터를 가리키고 있는경우
			if (m_pArr->size() - 1 == m_index)
			{
				m_index = -1;
			}
			else
			{
				++m_index;
			}


			return *this;
		}

		//++후위
		iterator operator ++(int)
		{
			iterator copy_iter = *this;

			++(*this);

			return copy_iter;
		}



		bool operator ==(const iterator& _other)
		{
			if (this->m_pData == _other.m_pData && m_index == _other.m_index)
			{
				return true;
			}

			return false;
		}

		bool operator !=(const iterator& _other)
		{
			return !(*this == _other);
		}


	public:
		iterator() :m_pArr(nullptr), m_pData(nullptr), m_index(-1), m_bValid(false)
		{
		}

		iterator(CArr* _pArr, T* _pData, int _index) : m_pArr(_pArr), m_pData(_pData), m_index(_index), m_bValid(false)
		{
			if (nullptr != _pArr && 0 <= m_index)
			{
				m_bValid = true;
			}
		}

		~iterator()
		{
		}

		friend class CArr; //iter가 CArr friend 선언
	};
};

template<typename T>
void CArr<T>::Resize(int _iResizeCount)
{
	//Exceptional case
	if (_iResizeCount <= m_iMaxCount)
	{
		assert(nullptr);
	}

	T* NewArr = new T[_iResizeCount];

	for (int i = 0; i < m_iCount; ++i)
	{
		NewArr[i] = m_pData[i];
	}

	delete[] m_pData;

	m_pData = NewArr;

	m_iMaxCount = _iResizeCount;
}

template<typename T>
void CArr<T>::PushBack(const T& _Data)
{
	if (m_iMaxCount <= m_iCount)
	{
		Resize(m_iMaxCount * 2);
	}
	m_pData[m_iCount++] = _Data;
}



template<typename T>
T& CArr<T>::operator[](int idx)
{
	return *(m_pData + idx);
}

template<typename T>
typename CArr<T>::iterator CArr<T>::begin() //반환 타입이 InnerClass 일경우 typename 과 포함된클래스와 이터레이터를 명시해줘야함
{
	if (0 == m_iCount)
	{
		return iterator(this, m_pData, -1); //데어터가 없는경우 begin() == end()
	}

	return iterator(this, m_pData, 0); //임시 객체: 변수명을 만들어주지 않고 바로 리턴
}

template<typename T>
typename CArr<T>::iterator CArr<T>::end() //반환 타입이 InnerClass 일경우 typename 과 포함된클래스와 이터레이터를 명시해줘야함
{
	return iterator(this, m_pData, -1);
}

template<typename T>
typename CArr<T>::iterator CArr<T>::erase(iterator& iter)
{
	//예외처리: iter가 다른 배열을 가리키고 있을경우// iter가 end iter일 경우 // 가변배열에 데이터가 없을경우
	if (iter.m_pArr != this || end() == iter || iter.m_index >= m_iCount)
	{
		assert(nullptr);
	}

	for (int i = iter.m_index; i < m_iCount - 1; ++i)
	{
		m_pData[i] = m_pData[i + 1];
	}

	iter.m_bValid = false;

	--m_iCount;
	return iterator(this, m_pData, iter.m_index);
}
template<typename T>
void CArr<T>::clear()
{
	m_iCount = 0;
}

template<typename T>
CArr<T>::CArr() : m_pData(nullptr), m_iCount(0), m_iMaxCount(2)
{
	m_pData = new T[2]; //컴파일러에게 판단의 근거 를 주기 위해- >자료데이터형* 변수명 = new 자료데이터형 이렇게 C++ 에서 변경된것이다
}
template<typename T>
CArr<T>::~CArr()
{
	delete[] m_pData;
}


