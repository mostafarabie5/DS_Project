#pragma once
template<class ItemType>
class PriorityQueueInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool add(const ItemType& newEntry) = 0;
	virtual bool remove(int position) = 0;
	virtual ItemType peek() const = 0;
};

