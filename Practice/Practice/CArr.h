#pragma once

#include <assert.h>
//iterator operator override
//[] operator override
//pushback
//resize
//
template<typename T>
class CArr
{
private:
	T* m_pData;
	int m_Count;
	int m_MaxCount;

public:
	CArr(int _maxCount);
	CArr();
	~CArr();
	void push_back(const T& iData);
	void resize(int _iResizeCount);
	int size() { return m_Count; }
	int capacity() { return m_MaxCount; }
	T& operator [] (int index);

	//CArray[2]=100;
	class iterator;
	iterator begin();
	iterator end();
	iterator erase(iterator& _iter);
	void clear()
	{
		m_Count = 0;
	}

	class iterator
	{
	private:
		CArr* m_pArr; //iterator 가 가리킬 데이터를 관리하는 가변배열 주소
		T* m_pData; //데이터들의 시작 주소
		int m_index; //가리키는 데이터의 인덱스
		bool m_bValid; // iterator 유효성 체크 Erase 함수 참고

	public:
		iterator();
		iterator(CArr* _pCArr, T* _m_pData, int _m_index);
		~iterator();


		//친구관계인 클래스는 Private 멤버들도 공유할 수 있는 기능제공
		//공유를 해줘야하는 클래스가 friend class 를 선언해줘야함 
		friend class CArr;

		//예외: iter가 end iter거나 알고있는 주소와 가변배열이 알고있는 주소가 다를경우 또는 end iterator를 가리키고 있는경우
		T& operator * ()
		{
			if (-1 == m_index || m_pData != m_pArr->m_pData || !m_bValid)
			{
				assert(nullptr);
			}
			return m_pData[m_index];
		}

		bool operator == (const iterator& _otherIter)
		{
			if (m_pData == _otherIter.m_pData && m_index == _otherIter.m_index)
			{
				return true;
			}
			return false;
		}

		bool operator != (const iterator& _otherIter)
		{
			return !(*this == _otherIter);
		}

		iterator& operator ++() //prefix
		{
			//iter가 end iter거나 알고있는 주소와 가변배열이 알고있는 주소가 다를경우
			if (-1 == m_index || this->m_pData != m_pArr->m_pData)
			{
				assert(nullptr);
			}

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

		iterator operator ++(int) //후위 연산 postfix
		{
			iterator Copyiter = *this;

			++(*this);

			return Copyiter;
		}


		iterator& operator --() //prefix
		{
			//iter가 end iter거나 알고있는 주소와 가변배열이 알고있는 주소가 다를경우
			if (-1 == m_index || this->m_pData != m_pArr->m_pData)
			{
				assert(nullptr);
			}

			if (m_pArr->size() - 1 == m_index)
			{
				m_index = -1;
			}
			else
			{
				--m_index;
			}

			return *this;
		}

		iterator operator --(int) //후위 연산 postfix
		{
			iterator Copyiter = *this;

			--(*this);

			return Copyiter;
		}

	};
};


template<typename T>
CArr<T>::CArr() : m_pData(nullptr), m_Count(0), m_MaxCount(2)
{
	m_pData = new T[m_MaxCount];
}
template<typename T>
CArr<T>::CArr(int _maxCount) : m_pData(nullptr), m_Count(0), m_MaxCount(_maxCount)
{
	m_pData = new T[m_MaxCount];
}

template<typename T>
void CArr<T>::push_back(const T& _iData)
{
	if (m_Count >= m_MaxCount)
	{
		resize(m_MaxCount * 2); //기존 맥스카운트에서 2배로 만들기
	}

	m_pData[m_Count++] = _iData;
}

template<typename T>
void CArr<T>::resize(int _iResizeCount)
{
	//ResizeCount가 기존 카운트보다 작으면 예외처리
	if (_iResizeCount <= m_MaxCount)
	{
		assert(nullptr);
	}

	T* ExtendedArr = new T[_iResizeCount];

	for (int i = 0; i < m_MaxCount; ++i)
	{
		ExtendedArr[i] = m_pData[i];
	}

	delete[] m_pData;

	m_pData = ExtendedArr;

	m_MaxCount = _iResizeCount;
}
template<typename T>
T& CArr<T>::operator[](int index)
{
	return *(m_pData + index);
}
template <typename T>
CArr<T>::~CArr()
{
	delete[] m_pData;
}

template<typename T>
CArr<T>::iterator::iterator() : m_pArr(nullptr), m_pData(nullptr), m_index(-1), m_bValid(false)
{
}

template<typename T>
CArr<T>::iterator::iterator(CArr* _pCArr, T* _m_pData, int _m_index) : m_pArr(_pCArr), m_pData(_m_pData), m_index(_m_index), m_bValid(false)
{
	if (nullptr != _pCArr && 0 <= _m_index)
	{
		m_bValid = true;
	}
}
template<typename T>
CArr<T>::iterator::~iterator()
{
}

template<typename T>
typename CArr<T>::iterator CArr<T>::begin()
{
	if (0 == m_Count)
		return iterator(this, m_pData, -1);

	return iterator(this, m_pData, 0);
}

template<typename T>
typename CArr<T>::iterator CArr<T>::end()
{
	return iterator(this, m_pData, -1);
}

template<typename T>
typename CArr<T>::iterator CArr<T>::erase(iterator& _iter)
{
	//예외처리: 해당 iter가 다른 가변배열을 가리키고 있을때
	if (_iter.m_pArr != this || end() == _iter || m_Count <= _iter.m_index)
	{
		assert(nullptr);
	}
	//iterator 가 가리키는 데이터를 배열 내에서 제거한다. //뒷쪽에 있는걸 앞으로 땡기는거 //그럼 땡겨온 뒷쪽 데이터는?? A: 냅둬도 되 어차피 다음데이터가 거기로 들어갈꺼기 때문에
	for (int i = _iter.m_index; i < m_Count - 1; ++i)
	{
		m_pData[i] = m_pData[i + 1];
	}

	_iter.m_bValid = false;

	//카운트 감소
	--m_Count;

	return iterator(this, m_pData, _iter.m_index); //return iterator(_iter); 도가능함 그냥 그대로 돌려주는거기 때문에 
}




