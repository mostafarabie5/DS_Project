#pragma once
#include "QueueADT.h"
#include"Node.h"
#include<iostream>
#include"../Process/Process.h"
using namespace std;

class Process;

template<class ItemType>
class Queue :public QueueADT<ItemType>
{
private:
	int counter;
	Node<ItemType>* backPtr;
	Node<ItemType>* frontPtr;
public:
	Queue();
	Queue(const Queue<ItemType>& LQ);  	//copy constructor
	bool isEmpty() const;
	bool enqueue(const ItemType& newEntry);
	bool dequeue(ItemType& frntEntry);
	bool peek(ItemType& frntEntry)  const;
	void Print(int num, string s)const;
	int Getcount()const;
	~Queue();
};

template <class ItemType>
inline void Queue<ItemType>::Print(int num, string s)const
{
	cout << num << s;
	Node<ItemType>* curr = frontPtr;
	if (!curr)
	{
		cout << endl;
		return;
	}
	while (curr)
	{
		cout << curr->getItem();
		curr=curr->getNext();
		if (curr)
			cout << " , ";
	}
	cout << endl;
}
template<>
inline void Queue<Pair>::Print(int num, string s)const
{
	cout << num << s;
	Node<Pair>* curr = frontPtr;
	if (!curr)
		return;
	while (curr)
	{
		curr->getItem().Print();
		curr = curr->getNext();
		if (curr)
			cout << " , ";

	}
	cout << endl;
}


template<typename ItemType>
Queue<ItemType>::Queue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	counter = 0;
}


template<typename ItemType>
Queue<ItemType>::Queue(const Queue<ItemType>& LQ)
{
	counter = LQ.counter;
	Node<ItemType>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<ItemType>* ptr = new Node<ItemType>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<ItemType>* ptr = new Node<ItemType>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

template<typename ItemType>
bool Queue<ItemType>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template <typename ItemType>
bool Queue<ItemType>::enqueue(const ItemType& newEntry)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	counter++;
	return true;
} // end enqueue

template<typename ItemType>
bool Queue<ItemType>::dequeue(ItemType& frntEntry)
{
	if (isEmpty())
	{
		return false;
	}

	Node<ItemType>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	counter--;
	return true;

}

template<typename ItemType>
bool Queue<ItemType>::peek(ItemType& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}


template<typename ItemType>
int Queue<ItemType>::Getcount()const
{
	return counter;
}

template<typename ItemType>
Queue<ItemType>::~Queue()
{
	ItemType temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}



