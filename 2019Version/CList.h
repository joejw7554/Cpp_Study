#pragma once
#include "assert.h"
template<typename T>
class tListNode
{
public:
	T data;
	tListNode<T>* pPrev;
	tListNode<T>* pNext;

	tListNode() : data(), pPrev(nullptr), pNext(nullptr)
	{

	}
	tListNode(const T& _data, tListNode<T>* _pPrev, tListNode<T>* _pNext) : data(_data), pPrev(_pPrev), pNext(_pNext)
	{

	}
};

template<typename T>
class CList
{
private:
	tListNode<T>* m_pHead;
	tListNode<T>* m_pTail;
	int m_iCount;

public:
	void push_back(const T& _data);
	void push_front(const T& _data);
	int size() { return m_iCount; }

public:
	class iterator;
	iterator begin();
	iterator end();
	iterator erase(iterator& _startpoint, iterator& _endpoint);
	iterator insert(const iterator& _iter, const T& Data);

public:
	CList();
	~CList();

	class iterator
	{

	private:
		CList<T>* m_pList;
		tListNode<T>* m_pNode; //null 인겨우 , end iterator로 간주
		bool			m_bValid;

	public:
		T& operator * ()
		{
			return m_pNode->data;
		}

		bool operator == (const iterator& _other)
		{
			if (_other.m_pList == m_pList && m_pNode == _other.m_pNode)
			{
				return true;
			}

			return  false;
		}

		bool operator != (const iterator& _other)
		{
			return !(*this == _other);
		}

		iterator& operator ++ ()
		{
			//end 에서 ++ 한경우
			if (nullptr == m_pNode || !m_bValid)
			{
				assert(nullptr);
			}

			m_pNode = m_pNode->pNext;

			return *this;
		}

		iterator operator ++ (int)
		{
			iterator copyIter = *this;

			++(*this);

			return copyIter;
		}


		iterator& operator -- ()
		{
			if (nullptr == m_pNode || !m_bValid)
			{
				assert(nullptr);
			}

			m_pNode = m_pNode->pPrev;

			return *this;
		}

		iterator operator -- (int)
		{
			iterator copyIter = *this;

			--(*this);

			return copyIter;
		}


	public:
		iterator() : m_pList(nullptr), m_pNode(nullptr), m_bValid(false)
		{
		}

		iterator(CList<T>* _pList, tListNode<T>* _pNode) : m_pList(_pList), m_pNode(_pNode), m_bValid(false)
		{
			if (nullptr != _pList && nullptr != _pNode)
			{
				m_bValid = true;
			}
		}
		~iterator()
		{
		}

		friend class CList;

	};
};

template<typename T>
void CList<T>::push_back(const T& _data)
{
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, nullptr);

	//처음 입력된 데이터가 아니라면
	if (nullptr == m_pHead)
	{
		m_pHead = pNewNode;
		m_pTail = pNewNode;
	}
	else
	{
		m_pTail->pNext = pNewNode;
		pNewNode->pPrev = m_pTail;

		m_pTail = pNewNode;
	}
	++m_iCount;
}

template<typename T>
void CList<T>::push_front(const T& _data)
{
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, m_pHead);

	m_pHead->pPrev = pNewNode;

	m_pHead = pNewNode;

	++m_iCount;
}



template<typename T>
typename CList<T>::iterator CList<T>::erase(iterator& _startpoint, iterator& _endpoint)
{
	//예외처리??
	if (this != _startpoint || this != _endpoint)
	{
		assert(nullptr);
	}

	//반복문 처리 시작지점은 이터가 가리키는곳
	//반복횟수는?
	//반복내용은?


	return iterator();
}

template<typename T>
typename CList<T>::iterator CList<T>::insert(const iterator& _iter, const T& _data)
{
	if (end() == _iter)
	{
		assert(nullptr);
	}

	//_iter.m_pNode->pPrev, _iter.m_pNode 를 넣으면 되지않을까???
	tListNode<T>* InsertNode = new tListNode<T>(_data, nullptr, nullptr);

	if (_iter.m_pNode == m_pHead)
	{
		m_pHead->pPrev = InsertNode;
		InsertNode->pNext = _iter.m_pNode;

		m_pHead = InsertNode;
	}

	else
	{
		//새로운 노드주소 이전주소를 이터 전노드와 연결
		_iter.m_pNode->pPrev->pNext = InsertNode;
		InsertNode->pPrev = _iter.m_pNode->pPrev;

		//새로운 노드주소 다음주소를 이터 현노드와 연결
		_iter.m_pNode->pPrev = InsertNode;
		InsertNode->pNext = _iter.m_pNode;
	}

	++m_iCount;

	return iterator(this, InsertNode);
}

template<typename T>
CList<T>::CList() : m_pHead(nullptr), m_pTail(nullptr), m_iCount(0)
{

}

template<typename T>
CList<T>::~CList()
{
	tListNode<T>* pDeleteNode = m_pHead;

	while (pDeleteNode)
	{
		tListNode<T>* pNext = pDeleteNode->pNext;
		delete pDeleteNode;
		pDeleteNode = pNext;
	}
}

template<typename T>
typename CList<T>::iterator CList<T>::begin()
{
	return iterator(this, m_pHead);
}

template<typename T>
typename CList<T>::iterator CList<T>::end()
{
	return iterator(this, nullptr);
}


