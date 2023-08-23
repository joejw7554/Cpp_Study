#pragma once
#include "assert.h"


template<typename T>
class TArray
{
private:
	T* pData;
	int Count;
	int MaxCount;

public:
	void push_back(const T& _Data);
	void resize(int _NewSize);
	inline  int size() { return Count; }
	inline int capacity() { return MaxCount; }


	TArray() : pData(nullptr), Count(0), MaxCount(2)
	{
		pData = new T[MaxCount];
	}
	TArray(const int _MaxCount) : pData(nullptr), Count(0), MaxCount(_MaxCount) //Const 가능?
	{
		pData = new T[MaxCount];
	}
	~TArray()
	{
		delete[] pData;
	}

	T& operator [](const int _index)
	{
		return *(pData + _index);
	}

	class iterator;
	iterator begin();
	iterator end();
	iterator erase(iterator& iter);
	iterator erase(iterator& _StartIter, iterator& _LastIter);
	void clear();

	class iterator
	{
	private:
		TArray* pArr;
		T* pArrData;
		int Index;

	public:
		iterator& operator ++()
		{
			//예외처리 :마지막 가변배열 마지막 인덱스에서 ++할 경우
			if (pArr->pData != pArrData || -1 == Index)
			{
				assert(nullptr);
			}

			if (pArr->size() - 1 == Index)
			{
				Index = -1;
			}
			else
			{
				++Index;
			}
			return *this;
		}

		iterator operator ++ (int) //후위
		{
			iterator NewIter = *this;

			++(*this);

			return NewIter;
		}

		T& operator * ()
		{
			if (pArr->pData != pArrData || Index == -1)
			{
				assert(nullptr);
			}
			return pArrData[Index];
		}

		iterator& operator --()
		{
			//예외처리 :마지막 가변배열 마지막 인덱스에서 ++할 경우
			if (pArr->pData != pArrData || -1 == Index)
			{
				assert(nullptr);
			}

			if (0 == Index)
			{
				Index = -1;
			}
			else
			{
				--Index;
			}
			return *this;
		}

		iterator operator -- (int) //후위
		{
			iterator NewIter = *this;

			--(*this);

			return NewIter;
		}

		iterator& operator +(int Number)
		{
			this->Index += Number;
			return *this;
		}

		iterator& operator -(int Number)
		{
			this->Index -= Number;
			return *this;
		}

		bool operator ==(const iterator& _other)
		{
			if (pArr != _other.pArr)
			{
				assert(nullptr);
			}

			if (pArrData == _other.pArrData && Index== _other.Index)
			{
				return true;
			}
			return false;
		}

		bool operator !=(const iterator& _other)
		{
			return !(*this == _other);
		}

		iterator() : pArr(nullptr), pArrData(nullptr), Index(-1)
		{

		}

		iterator(TArray* _Address, T* _Data, int _Index) : pArr(_Address), pArrData(_Data), Index(_Index)
		{
		}
		friend class TArray;
	};

};

template<typename T>
void TArray<T>::push_back(const T& _Data)
{
	//가변배열 사이즈 꽉창면 가변배열 늘려주기
	if (MaxCount <= Count)
	{
		resize(MaxCount + 1);
	}

	pData[Count++] = _Data;
}

template<typename T>
void TArray<T>::resize(int _NewSize)
{
	//새로운 공간 생성
	//데이터들 새로운곳에 복사
	//기존 포인터 삭제
	//새로운 데이터 복사 배열 주소 재배정

	if (_NewSize <= MaxCount) //요청 사이즈가 기존 맥스보다 낮으면 에러처리
	{
		assert(nullptr);
	}
	T* NewpArr = new T[_NewSize];

	for (int i = 0; i < _NewSize; ++i)
	{
		NewpArr[i] = pData[i];
	}
	delete[] pData;
	pData = NewpArr;
	MaxCount = _NewSize;
}

template<typename T>
typename TArray<T>::iterator TArray<T>::begin()
{
	if (0==Count)
	{
		return iterator(this, pData, -1);
	}

	return iterator(this, pData, 0);
}

template<typename T>
typename TArray<T>::iterator TArray<T>::end()
{
	return iterator(this, pData, -1);
}

template<typename T>
typename TArray<T>::iterator TArray<T>::erase(iterator& _iter)
{
	if (end()==_iter|| _iter.Index>=Count|| _iter.mPArr!=this)
	{
		assert(nullptr);
	}


	int LoopCount = _iter.Index;
	for (int i = _iter.Index; i < Count - 1; ++i)
	{
		_iter.pArrData[i] = _iter.pArrData[i + 1];
	}

	--Count;

	return iterator(this, pData, _iter.Index);
}

template<typename T>
typename TArray<T>::iterator TArray<T>::erase(iterator& _StartIter, iterator& _LastIter)
{
	if (Count <= _StartIter.Index || Count <= _LastIter.Index)
	{
		assert(nullptr);
	}
	
	for (int i=0; )
	{
		_iter.pArr[_StartIter.Index]=
		--Count;
	}

	return iterator();
}


