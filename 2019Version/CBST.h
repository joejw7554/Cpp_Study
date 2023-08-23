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
};

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
	bool Insert(const tPair<T1, T2>& _pair);

public:
	CBST() :m_pRoot(nullptr), m_iCount(0)
	{}
};

template<typename T1, typename T2>
bool CBST<T1, T2>::Insert(const tPair<T1, T2>& _pair)
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
				pNewNode->pParent = pNode;
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
