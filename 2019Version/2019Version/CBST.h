#pragma once
#include "assert.h";

enum class NODE_TYPE
{
	PARENT, //0
	LCHILD, //1
	RCHILD, //2
	END,	//3 마감
};


template<typename T1, typename T2>
struct tPair
{
	T1 first;
	T2 second;

	tPair() :first(), second()
	{}

	tPair(T1 _first, T2 _second) : first(_first), second(_second)
	{}
};

template<typename T1, typename T2>
tPair<T1, T2> make_bstpair(const T1& _first, const T2& _second)
{
	return tPair<T1, T2>(_first, _second );
}

template<typename T1, typename T2>
struct tBSTNode
{
	tPair<T1, T2>		pair;
	tBSTNode* arrNode[(int)NODE_TYPE::END];

	bool IsRoot()
	{
		if (nullptr == arrNode[(int)NODE_TYPE::PARENT])
			return true;

		return false;
	}


	bool IsLeftChild()
	{
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == this)
			return true;

		return false;
	}

	bool IsRightChild()
	{
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] == this)
			return true;

		return false;
	}

public:
	tBSTNode() : pair(), arrNode()
	{}

	tBSTNode(const tPair<T1, T2>& _pair, tBSTNode* _pParent, tBSTNode* _pLChild, tBSTNode* _pRChild)
		: pair(_pair), arrNode{ _pParent,_pLChild, _pRChild }
	{}
};

template<typename T1, typename T2>
class CBST
{
private:
	tBSTNode<T1, T2>* m_pRoot; //루트 노드 주소
	int m_iCount; //데이터 개수

public:
	bool insert(const tPair<T1, T2>& _pair);
	tBSTNode<T1, T2>* GetInOrderSuccessor(tBSTNode<T1, T2>* _pNode);
	tBSTNode<T1, T2>* GetInOrderPredecessor(tBSTNode<T1, T2>* _pNode);

	class iterator;
	iterator begin();
	iterator end();
	iterator find(const T1& _find);

public:
	CBST() :m_pRoot(nullptr), m_iCount(0)
	{}

	class iterator
	{
	private:
		CBST<T1, T2>* m_pBST;
		tBSTNode <T1, T2>* m_pNode; //if it's nullptr then consider an end iterator
	public:
		bool operator == (const iterator& _other)
		{
			if (m_pBST == _other.m_pBST && m_pNode == _other.m_pNode)
				return true;

			return false;
		}

		bool operator !=(const iterator& _other)
		{
			return !(*this == _other);
		}

		const tPair<T1, T2>* operator -> ()
		{
			assert(m_pNode);

			return &m_pNode->pair;
		}
		const tPair<T1, T2>& operator * ()
		{
			//Exception checking nullptr(Ex. end iter)
			assert(m_pNode);

			return m_pNode->pair;
		}

		iterator& operator ++()
		{
			m_pNode = m_pBST->GetInOrderSuccessor(m_pNode);
			return *this;
		}

	public:
		iterator()
		{}
		iterator(CBST<T1,T2>* _m_pBST, tBSTNode<T1,T2>* _m_pNode): m_pBST(_m_pBST), m_pNode(_m_pNode)
		{}
		~iterator()
		{}

	};
};

template<typename T1, typename T2>
bool CBST<T1, T2>::insert(const tPair<T1, T2>& _pair)
{
	tBSTNode<T1, T2>* pNewNode = new tBSTNode<T1, T2>(_pair, nullptr, nullptr, nullptr);

	//첫번째 데이터이면
	if (nullptr == m_pRoot)
	{
		m_pRoot = pNewNode;
	}
	else
	{
		tBSTNode<T1, T2>* pNode = m_pRoot;
		NODE_TYPE node_type = NODE_TYPE::END;

		while (true)
		{
			//방향을 정하는것: Enum과 Array를 사용하여
			if (pNode->pair.first < pNewNode->pair.first)
			{
				node_type = NODE_TYPE::RCHILD;
			}
			else if (pNode->pair.first > pNewNode->pair.first)
			{
				node_type = NODE_TYPE::LCHILD;
			}
			else
			{
				return false;
			}

			if (nullptr == pNode->arrNode[(int)node_type])
			{
				pNode->arrNode[(int)node_type] = pNewNode;
				pNewNode->arrNode[(int)NODE_TYPE::PARENT] = pNode;
				break;
			}
			else
			{
				pNode = pNode->arrNode[(int)node_type];
			}
		}
	}
	++m_iCount;
	return true;
}

template<typename T1, typename T2>
 tBSTNode<T1, T2>* CBST<T1, T2>::GetInOrderSuccessor(tBSTNode<T1, T2>* _pNode)
{
	 tBSTNode<T1, T2>* pSuccessor = nullptr;
	 //1. 오른쪽 자식이 있는경우 //오른쪽 자식으로 가서, 왼쪽이 없을때까지 내려감
	 if (nullptr!= _pNode->arrNode[(int)NODE_TYPE::RCHILD])
	 {
		 pSuccessor = _pNode->arrNode[(int)NODE_TYPE::RCHILD];

		 while (pSuccessor->arrNode[(int)NODE_TYPE::LCHILD])
		 {
			 pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::LCHILD];
		 }
	 }
	 //2. 오른쪽이 없다면 부모로부터 왼쪽 자식일 때 까지 위로 올라감
	//그때 부모가 후속자
	 else 
	 {
		 pSuccessor = _pNode;

		 while (true)
		 {
			 //더이상 위쪽으로 갈 수 없다 ==> 마지막 노드
			 if (pSuccessor->IsRoot())
			 {
				 return nullptr;
			 }
			 //부모로부터 왼쪽자식자식인지 체크
			 if (pSuccessor->IsLeftChild())
			 {
				 pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
				 break;
			 }
			 else
			 {
				 pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
			 }
		 }
	 }

	return pSuccessor;
}

template<typename T1, typename T2>
 tBSTNode<T1, T2>* CBST<T1, T2>::GetInOrderPredecessor(tBSTNode<T1, T2>* _pNode)
{
	 return NULL;
}

template<typename T1, typename T2>
typename CBST<T1, T2>::iterator CBST<T1, T2>::begin() //inodrder traversal
{
	tBSTNode<T1,T2>* pNode= m_pRoot;

	while (pNode->arrNode[(int)NODE_TYPE::LCHILD])
	{
		pNode = pNode->arrNode[(int)NODE_TYPE::LCHILD];
	}
	return iterator(this, pNode);
}

template<typename T1, typename T2>
typename CBST<T1, T2>::iterator CBST<T1, T2>::end() //nullptr is considered as end iter
{
	return iterator(this, nullptr);
}

template<typename T1, typename T2>
 typename CBST<T1,T2>::iterator CBST<T1, T2>::find(const T1& _find) //
{
	 tBSTNode<T1,T2>* pNode = m_pRoot;
	 NODE_TYPE node_type = NODE_TYPE::END;
	 while (pNode)
	 {
		 if (pNode->pair.first < _find)
		 {
			 node_type = NODE_TYPE::RCHILD;
		 }
		 else if (pNode->pair.first > _find)
		 {
			 node_type = NODE_TYPE::LCHILD;
		 }
		 else//found it just keep the node address and escape the loop!
		 {
			 break;
		 }

		 if (pNode->arrNode[(int)node_type] == nullptr) //when couldn't find it and set it to nullptr;
		 {
			 pNode == nullptr;
			 break;
		 }
		 else
		 {
			 pNode = pNode->arrNode[(int)node_type];
		 }
	 }
	 return iterator(this, pNode); //depending on the loop result it will return different result:  valid key address, failed->return nullptr in iter

}
