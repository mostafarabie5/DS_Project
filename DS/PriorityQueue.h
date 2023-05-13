#pragma once
#include "PriorityQueueInterface.h"
#include"LinkedSortedList.h"
template<class ItemType>
class PriorityQueue :public PriorityQueueInterface<ItemType>
{
private:
	LinkedSortedList<ItemType>* slistPtr; // Pointer to sorted list of
	// items in the priority queue
public:
	PriorityQueue();

	PriorityQueue(const PriorityQueue& pq);

	~PriorityQueue();

	bool isEmpty() const;

	bool add(const ItemType& newEntry);
	bool add2(const ItemType& newEntry);

	bool remove(int position);
	ItemType peek() const;

	int getLength()const;

	void Print(bool b)const;
}; // end PriorityQueue



template<class ItemType>
PriorityQueue<ItemType>::PriorityQueue()
{
	slistPtr = new LinkedSortedList<ItemType>();
}

template<class ItemType>
inline PriorityQueue<ItemType>::PriorityQueue(const PriorityQueue& pq)
{
}

template<class ItemType>
inline PriorityQueue<ItemType>::~PriorityQueue()
{
}

template<class ItemType>
bool PriorityQueue<ItemType>::isEmpty() const
{
	return slistPtr->isEmpty();
}

template<class ItemType>
bool PriorityQueue<ItemType>::add(const ItemType& newEntry)
{
	slistPtr->insertSorted(newEntry);
	return true;
} // end add

template<class ItemType>
inline bool PriorityQueue<ItemType>::add2(const ItemType& newEntry)
{
	slistPtr->insertSorted2(newEntry);
	return true;
}

template<class ItemType>
bool PriorityQueue<ItemType>::remove(int position)
{
	// The highest-priority item is at the end of the sorted list
	return slistPtr->remove(position);
} // end remove


template<class ItemType>
ItemType PriorityQueue<ItemType>::peek() const
{
	return slistPtr->getEntry(1);
}

template<class ItemType>
int PriorityQueue<ItemType>::getLength() const
{
	return slistPtr->getLength();
}

template<class ItemType>
void PriorityQueue<ItemType>::Print(bool b) const
{
	slistPtr->Print(b);
}
