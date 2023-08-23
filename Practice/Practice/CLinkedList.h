#pragma once

template<typename T>
class Node
{
public:
	T Data;
	Node<T>* PrevNode;
	Node<T>* NextNode;
public:
	Node();
	Node(const T& _Data, Node<T>* _PrevNode, Node<T>* _NextNode);
};
template<typename T>
Node<T>::Node() : Data(), PrevNode(nullptr), NextNode(nullptr)
{
}
template<typename T>
Node<T>::Node(const T& _Data, Node<T>* _PrevNode, Node<T>* _NextNode) : Data(_Data), PrevNode(_PrevNode), NextNode(_NextNode)
{
}

template<typename T>
class CList
{
private:
	Node<T>* HeadNode;
	Node<T>* TailNode;
	int Count;

public:
	CList();
	~CList();
	void pushback(const T& Data);
	void pushfront(const T& Data);
};


template<typename T>
CList<T>::CList() : HeadNode(nullptr), TailNode(nullptr), Count(0)
{
}
template<typename T>
CList<T>::~CList()
{
	Node<T>* DeleteNode = HeadNode;

	while (DeleteNode)
	{
		Node<T>* pNext = DeleteNode->NextNode;
		delete DeleteNode;
		DeleteNode = pNext;
	}
}
template<typename T>
void CList<T>::pushback(const T& Data)
{
	Node<T>* NewNode = new Node<T>(Data, nullptr, nullptr);

	if (nullptr == HeadNode)
	{
		HeadNode = NewNode;
		TailNode = NewNode;
	}
	else
	{
		TailNode->NextNode = NewNode;
		NewNode->PrevNode = TailNode;
		TailNode = NewNode;
	}
	++Count;
}
template<typename T>
void CList<T>::pushfront(const T& Data)
{
	Node<T>* NewNode = new Node<T>(Data, nullptr, HeadNode);

	HeadNode->PrevNode = NewNode;

	HeadNode = NewNode;

	++Count;
}