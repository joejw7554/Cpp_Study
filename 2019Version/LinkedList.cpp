#include "LinkedList.h"
#include "iostream"

void InitList(tLinkedList* _pList)
{
	_pList->pHeadNode = nullptr;
	_pList->iCount = 0;
}

void PushBack(tLinkedList* _pList, int Data)
{
	//created a TagNode to save data
	//Insert Data
	tNode* pNode = (tNode*)malloc(sizeof(tNode));
	pNode->iData = Data;
	pNode->pNextNode = nullptr;

	if (0 == _pList->iCount)
	{
		_pList->pHeadNode = pNode;
	}
	else
	{
		//find the lastest node
		//해당 노드의 pNextNode 생성시킨 노드의 주소로 채움
		tNode* pCurFinalNode = _pList->pHeadNode;

		while (pCurFinalNode->pNextNode)
		{
			pCurFinalNode = pCurFinalNode->pNextNode;
		}

		pCurFinalNode->pNextNode = pNode;

	}
	++_pList->iCount;

}

void PushFront(tLinkedList* _pList, int Data)
{
	tNode* NewNode = (tNode*)malloc(sizeof(tNode));
	NewNode->iData = Data;
	NewNode->pNextNode = _pList->pHeadNode;

	_pList->pHeadNode = NewNode;

	++_pList->iCount;
}



void ReleaseList(tLinkedList* _pList)
{
	tNode* pDeleteNode = _pList->pHeadNode;

	while (pDeleteNode)
	{
		tNode* pNext = pDeleteNode->pNextNode;
		free(pDeleteNode);
		pDeleteNode = pNext;
	}
}
