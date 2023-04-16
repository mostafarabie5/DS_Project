#pragma once
#include "QueueADT.h"
#include"Node.h"
#include<iostream>
#include"Process.h"
using namespace std;

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
	void Print(int num,string s)const;
	int Getcount()const;
	//void operator =(Queue<ItemType> q);
	~Queue();
};

template <class ItemType>
inline void Queue<ItemType>::Print(int num, string s)const
{

}
//template<>
//inline void Queue<Process*>::Print(int num, string s)const
//{
//	cout << num << s;
//	Node<Process*> curptr;
//}

//template<>
//inline void Queue<Process*>::Print(int num, std::string s)const
// {
//	std::cout << num << s;
//	Node<Process*>* curptr = frontPtr;
//	if (!curptr)
//		return;
//
//	curptr->getItem();
//	curptr = curptr->getNext();
//	while (curptr)
//	{
//		std::cout << ", ";
//		curptr->getItem()->Print();
//		curptr = curptr->getNext();
//	}
//	std::cout << std::endl;
//}

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
		return false;

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


//template<class ItemType>
//inline void Queue<ItemType>::Print(int num, std::string s)const
//{
//	std::cout << num << s;
//	Node<ItemType>* curptr = frontPtr;
//	if (!curptr)
//		return;
//
//	std::cout << curptr->getItem();
//	curptr = curptr->getNext();
//	while (curptr)
//	{
//		std::cout << ", " << curptr->getItem();
//		curptr = curptr->getNext();
//	}
//	std::cout << std::endl;
//}



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

//template<typename ItemType>
//void Queue<ItemType>::operator=(Queue<ItemType> q)
//{
//	counter = q.counter;
//	backPtr = q.backPtr;
//	frontPtr = q.frontPtr;
//}





/*template<>
bool Queue<Pair>::dequeue(Pair& p)
{
	if (isEmpty())
		return false;

	Node<Pair>* nodeToDeletePtr = frontPtr;
	p = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	counter--;
	return true;
}
template<>
Queue<Pair>::~Queue()
{
	Pair p;
	while (dequeue(p));
}


/*template<>
void Queue<Pair>::Print(int num, std::string s)
{
	std::cout << num << s;
	Node<Pair>* curptr = frontPtr;
	if (!curptr)
		return;

	std::cout << curptr->getItem();
	curptr = curptr->getNext();
	while (curptr)
	{
		std::cout << ", " << curptr->getItem();
		curptr = curptr->getNext();
	}
	std::cout << std::endl;
}*/
//std::ostream& operator<<(std::ostream& out, Pair p)
//{
//	out << "(" << p.getFirst() << "," << p.getSecond() << "), ";
//	return out;
//}

