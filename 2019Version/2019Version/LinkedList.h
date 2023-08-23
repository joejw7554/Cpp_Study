#pragma once

typedef struct _tagNode
{
	int iData;
	_tagNode* pNextNode;

}tNode;

typedef struct _tagList
{
	tNode* pHeadNode;
	int iCount;
}tLinkedList;


void InitList(tLinkedList* _pList);

void PushBack(tLinkedList* _pList, int Data);

void PushFront(tLinkedList* _pList, int Data);

void ReleaseList(tLinkedList* _pList);

