#include "iostream"
#include "LinkedList.h"

using namespace std;

int main()
{
	
	tLinkedList List = {};

	InitList(&List);

	PushFront(&List, 100);
	PushFront(&List, 200);
	PushFront(&List, 300);

	tNode* pNode = List.pHeadNode;
	for (int i = 0; i < List.iCount; ++i)
	{
		printf("%d\n", pNode->iData);
		pNode = pNode->pNextNode;
	}

	ReleaseList(&List);
	return 0;


}