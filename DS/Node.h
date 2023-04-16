#pragma once
#include"Node.h"
template < typename ItemType>
class Node
{
private:
	ItemType item; // A data item
	Node<ItemType>* next; // Pointer to next node
public:
	Node();
	Node(const ItemType& r_Item);
	Node(const ItemType& r_Item, Node<ItemType>* nextNodePtr);
	void setItem(const ItemType& r_Item);
	void setNext(Node<ItemType>* nextNodePtr);
	ItemType getItem() const;
	Node<ItemType>* getNext() const;
}; // end Node


template < typename ItemType>
Node<ItemType>::Node()
{
	next = nullptr;
}

template < typename ItemType>
Node<ItemType>::Node(const ItemType& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename ItemType>
Node<ItemType>::Node(const ItemType& r_Item, Node<ItemType>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename ItemType>
void Node<ItemType>::setItem(const ItemType& r_Item)
{
	item = r_Item;
}

template < typename ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename ItemType>
ItemType Node<ItemType>::getItem() const
{
	return item;
}

template < typename ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
	return next;
}


