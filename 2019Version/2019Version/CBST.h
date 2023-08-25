#pragma once

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
		 if (_find < m_pRoot->pair.first)
		 {
			 node_type = NODE_TYPE::LCHILD;
		 }
		 else if (_find > m_pRoot->pair.first)
		 {
			 node_type = NODE_TYPE::RCHILD;
		 }
		 else//found it just kepp the node address and escape the loop!
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
