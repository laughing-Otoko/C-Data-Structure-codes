#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <cassert>

using namespace std;

template <class Type>
struct nodeType
{
	Type info;
	nodeType *link;

public:
	nodeType* buildListForward() {
		nodeType* first, * newNode, * last;
		int num;
		cout << "Enter a list of integers ending with -999." << endl;
		cin >> num;
		first = NULL;

		while (num != -999) {
			newNode = new nodeType;
			newNode->info = num;
			newNode->link = NULL;

			if (first == NULL) {
				first = newNode;
				last = newNode;
			}
			else {
				last->link = newNode;
				last = newNode;
			}

		}
	}
	nodeType* buildListBackward()
	{
		nodeType* first, * newNode;
		int num;

		cout << "Enter a list of integers ending with -999." << endl;
		cin >> num;

		while (num != -999) {
			newNode = new nodeType;
			newNode->info = num;
			newNdoe->link = first;

			first = newNode;

			cin >> num;
		}

		return first;
	}

};

template <class Type>
class linkedListIterator
{
public:
	linkedListIterator();
	linkedListIterator(nodeType<Type>* ptr);
	Type operator*();
	linkedListIterator<Type> operator++();
	bool operator==(const linkedListIterator<Type>& right) const;
	bool operator!=(const linkedListIterator<Type>& right) const;

private:
	nodeType<Type>* current;
};

template <class Type>
class linkedListType
{
public:
	const linkedListType<Type>& operator=(const linkedListType<Type>&);
	void initializeList();
	bool isEmptyList() const;
	void print() const;
	int length() const;
	void destroyList();
	Type front() const;
	Type back() const;
	virtual bool search(const Type& searchItem) const = 0;
	virtual void insertFirst(const Type& newItem) = 0;
	virtual void insertLast(const Type& newItem) const = 0;
	virtual void deleteNode(const Type& deleteItem) = 0;
	linkedListIterator<Type> begin();
	linkedListIterator<Type> end();
	linkedListType();
	linkedListType(const linkedListType<Type>& otherList);
	~linkedListType();
	void reversePrint(nodeType<Type>* current) const;
	void printListReverse() const;
	void deleteSmallest();

protected:
	int count;
	nodeType<Type>* first;
	nodeType<Type>* last;	

private:
	void copyList(const linkedListType<Type>& otherList);
};

template <class Type>
class unorderedLinkedList : public linkedListType<Type>
{
public:
	bool search(const Type& searchItem) const;
	void insertFirst(const Type& newItem);
	void insertLast(const Type& newItem);
	void deleteNode(const Type& deleteItem);
	void linkedInsertionSort();
	void divide(nodeType<Type>* first1, nodeType<Type>* first2);
	nodeType<Type>* mergeList(nodeType<Type>* first1, nodeType<Type>* first2);
	void recMergeSort(nodeType<Type>*& head);
	void mergeSort();
};

template <class Type>
class orderedLinkedList : public linkedListType<Type>
{
public:
	bool search(const Type& searchItem) const;
	void insert(const Type& newItem);
	void insertFirst(const Type& newItem);
	void insertLast(const Type& newItem);
	void deleteNode(const Type& deleteItem);
};
#endif //LINKEDLIST_H
template <class Type>
linkedListIterator<Type>::linkedListIterator()
{
	current = NULL;
}
template <class Type>
linkedListIterator<Type>::linkedListIterator(nodeType<Type>* ptr)
{
	current = ptr;
}
template <class Type>
Type linkedListIterator<Type>::operator*()
{
	return current->info;
}
template <class Type>
linkedListIterator<Type> linkedListIterator<Type>::operator++()
{
	current = current->link;
	return *this;
}
template <class Type>
bool linkedListIterator<Type>::operator==(const linkedListIterator<Type>& right) const
{
	return (current == right.current);
}
template <class Type>
bool linkedListIterator<Type>::operator!=(const linkedListIterator<Type>& right) const
{
	return (current != right.current);
}

//linkedListType:
template <class Type>
bool linkedListType<Type>::isEmptyList() const
{
	return (first == NULL);
}
template <class Type>
linkedListType<Type>::linkedListType()
{
	first = NULL;
	last = NULL;
	count = 0;
}
template <class Type>
void linkedListType<Type>::destroyList()
{
	nodeType<Type>* temp;
	
	while (first != NULL) {
		temp = first;
		first = first->link;
		delete temp;
	}
	last = NULL;
	count = 0;

}
template <class Type>
void linkedListType<Type>::initializeList()
{
	destroyList();
}
template <class Type>
void linkedListType<Type>::print() const
{
	nodeType<Type>* current;

	current = first;

	while (current != NULL) {
		cout << current->info << " ";
		current = current->link;
	}
}
template <class Type>
int linkedListType<Type>::length() const
{
	return count;
}
template <class Type>
Type linkedListType<Type>::front() const
{
	assert(first != NULL);

	return first->info;
}
template <class Type>
Type linkedListType<Type>::back() const
{
	assert(last != NULL);
	return last->info;
}
template <class Type>
linkedListIterator<Type> linkedListType<Type>::begin()
{
	linkedListType<Type> temp(first);
	return temp;
}
template <class Type>
linkedListIterator<Type> linkedListType<Type>::end()
{
	linkedListIterator<Type> temp(NULL);
	return temp;
}
template <class Type>
void linkedListType<Type>::copyList(const linkedListType<Type>& otherList)
{
	nodeType<Type>* newNode;
	nodeType<Type>* current;

	if (first != NULL)
		destroyList();

	if (otherList.first == NULL_)
	{
		first = NULL;
		last = NULL;
		count = 0;
	}
	else
	{
		current = otherList.first;
		count = otherList.count;

		first = new nodeType<Type>;
		first->info = current->info;
		first->link = NULL;
		last = first;
		current = current->link;

		while (current != NULL)
		{
			newNode = new nodeType<Type>;
			newNode->info = current->info;
			newNode->link = NULL;
			last->link = newNode;
			last = newNode;
			current = current->link;
		}
	}
}
template <class Type>
linkedListType<Type>::~linkedListType()
{
	destroyList();
}
template <class Type>
linkedListType<Type>::linkedListType(const linkedListType<Type>& otherList)
{
	first = NULL;
	copyList(otherList);
}
template <class Type>
const linkedListType<Type>& linkedListType<Type>::operator=(const linkedListType<Type>& otherList)
{
	if (this != &otherList)
	{
		copyList(otherList);
	}
	return *this;
}
template <class Type>
void linkedListType<Type>::reversePrint(nodeType<Type>* current) const
{
	if (current != NULL)
	{
		reversePrint(current->link);
		cout << current->info << " ";
	}
}
template <class Type>
void linkedListType<Type>::printListReverse() const
{
	reversePrint(first);
	cout << endl;
}

//unorderedLinkedList:
template <class Type>
bool unorderedLinkedList<Type>::search(const Type& searchItem) const
{
	nodeType<Type>* current;
	bool found = false;

	current = first;

	while (current != NULL && !found)
		if (current->info == searchItem)
			found = true;
		else
			current = current->link;
	return found;
}
template <class Type>
void unorderedLinkedList<Type>::insertFirst(const Type& newItem)
{
	nodeType<Type>* newNode;

	newNode = new nodeType<Type>;
	newNode->info = newItem;
	newNode->link = first;
	first = newNode;
	count++;

	if (last == NULL)
		last = newNode;
}
template <class Type>
void unorderedLinkedList<Type>::insertLast(const Type& newItem)
{
	nodeType<Type>* newNode;
	newNode = new nodeType<Type>;
	newNode->info = newItem;
	newNode->link = NULL;

	if (first == NULL)
	{
		first = newNode;
		last = newNode;
		count++;
	}
	else
	{
		last->link = newNode;
		last = newNode;

		count++;
	}
}
template <class Type>
void unorderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
	nodeType<Type>* current;
	nodeType<Type>* trailCurrent;
	bool found;

	if (first == NULL)
		cout << "Cannot delete from an empty list!" << endl;
	else
	{
		if (first->info == deleteItem) {
			current = first;
			first = first->link;
			count--;

			if (first == NULL)
				last = NULL:

			delete current;
		}
		else {
			found = false;
			trailCurrent = first;

			current = first->link;

			while (current != NULL && !found)
			{
				if (current->info != deleteItem)
				{
					trailCurrent = current;
					current = current->link;
				}
				else
					found = true;
			}

			if (found) {
				trailCurrent->link = current->link;
				count--;

				if (last == current)
					last = trailCurrent;
				delete current;
			}
			else
				cout << "The item to be deleted is not in the list." << endl;
		}
	}
}
template <class Type>
void unorderedLinkedList<Type>::linkedInsertionSort()
{
	nodeType<Type>* lastInOrder;
	nodeType<Type>* firstOutOfOrder;
	nodeType<Type>* current;
	nodeType<Type>* trailCurrent;

	lastInOrder = first;

	if (first == NULL)
		cerr << "Cannot sort an empty list." << endl;
	else if (first->link == NULL)
		cout << "The list is of length 1. It is already in order." << endl;
	else
		while (lastInOrder->link != NULL)
		{
			firstOutOfOrder = lastInOrder->link;

			if (firstOutOfOrder->info < first->info)
			{
				lastInOrder->link = firstOutOfOrder->link;
				firstOutOfOrder->link = first;
				first = firstOutOfOrder;
			}
			else
			{
				trailCurrent = first;
				current = first->link;

				while (current->info < firstOutOfOrder->info)
				{
					trailCurrent = current;
					current = current->link;
				}
				if (current != firstOutOfOrder)
				{
					lastInOrder->link = firstOutOfOrder->link;
					firstOutOfOrder->link = current;
					trailCurrent->link = firstOutOfOrder;
				}
				else
					lastInOrder = lastInOrder->link;
			}
		}
}
template <class Type>
void unorderedLinkedList<Type>::divide(nodeType<Type> *first1, nodeType<Type> *first2)
{
	nodeType<Type>* middle;;
	nodeType<Type>* current;

	if (first1 == NULL)
		first2 = NULL;
	else if (first1->link == NULL)
		first2 = NULL;
	else
	{
		middle = first1;
		current = first1->link;

		if (current != NULL)
			current = current->link;
		while (current != NULL)
		{
			middle = middle->link;
			current = current->link;
			if (current != NULL)
				current = current->link;
		}
		first2 = middle->link;
		middle->link = NULL;
	}
}
template <class Type>
nodeType<Type>* unorderedLinkedList<Type>::mergeList(nodeType<Type>* first1, nodeType<Type>* first2)
{
	nodeType<Type>* lastSmall;
	nodeType<Type>* newHead;

	if (first1 == NULL)
		return first2;
	else if (first2 == NULL)
		return first1;
	else
	{
		if (first1->info < first2->info)
		{
			newHead = first1;
			first1 = first1->link;
			lastSmall = newHead;
		}
		else
		{
			newHead = first2;
			first2 = first2->link;
			lastSmall = newHead;
		}
		while (first1 != NULL && first2 != NULL)
		{
			if (first1->info < first2->info)
			{
				lastSmall->link = first1;
				lastSmall = lastSmall->link;
				first1 = first1->link;
			}
			else
			{
				lastSmall->link = first2;
				lastSmall = lastSmall->link;
				first2 = first2->link;
			}
		}
		if (first1 == NULL)
			lastSmall->link = first2;
		else
			lastSmall->link = first1;
		
		return newHead;
	}
}
template <class Type>
void unorderedLinkedList<Type>::recMergeSort(nodeType<Type>*& head)
{
	nodeType<Type>* otherHead;

	if (head != NULL)
		if (head->link != NULL)
		{
			divide(head, otherHead);
			recMergeSort(head);
			recMergeSort(otherHead);
			head = mergeList(head, otherHead);
		}
}
template <class Type>
void unorderedLinkedList<Type>::mergeSort()
{
	recMergeSort(first);

	if (first == NULL)
		last = NULL;
	else
	{
		last = first;
		while (last->link != NULL)
			last = last->link;
	}
}
//orderedLinkedList
template <class Type>
bool orderedLinkedList<Type>::search(const Type& searchItem) const
{
	bool found = false;
	nodeType<Type>* current;
	
	current = first;

	while (current != NULL && !found)
		if (current->info >= searchItem)
			found = true;
		else
			current = current->link;
	
	if (found)
		found = (current->info == searchItem);

	return found;
}
template <class Type>
void orderedLinkedList<Type>::insert(const Type& newItem)
{
	nodeType<Type>* current;
	nodeType<Type>* trailCurrent;
	nodeType<Type>* newNode;

	bool found;
	current = first;
	while (current != NULL)
		if (current->info == newItem)
		{
			cout << "Item is already in the list!" << endl;
			return;
		}
		else
			current = current->link;

	newNode = new nodeType<Type>;
	newNode->info = newItem;
	newNode->link = NULL;

	if (first == NULL)
	{
		first = newNode;
		last = newNode;
		count++;
	}
	else {
		current = first;
		found = false;

		while (current != NULL && !found)
			if (current->info >= newItem)
				found = true;
			else {
				trailCurrent = current;
				current = current->link;
			}
		if (current == first)
		{
			newNode->link = first;
			first = newNode;
			count++;
		}
		else {
			trailCurrent->link = newNode;
			newNode->link = current;

			if (current == NULL)
				last = newNode;

			count++;
		}
	}

}
template<class Type>
void orderedLinkedList<Type>::insertFirst(const Type& newItem)
{
	insert(newItem);
}
template <class Type>
void orderedLinkedList<Type>::insertLast(const Type& newItem)
{
	insert(newItem);
}
template <class Type>
void orderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
	nodeType<Type>* current;
	nodeType<Type>* trailCurrent;
	bool found;

	if (first == NULL)
		cout << "Cannot delete from an empty list." << endl;
	else {
		current = first;
		found = false;

		while (current != NULL && !found)
			if (current->info >= deleteItem)
				found = true;
			else
			{
				trailCurrent = current;
				current = current->link;
			}
		if (current == NULL)
			cout << "The item to be deleted is not in the list." << endl;
		else
			if (current->info == deleteItem)
			{
				if (first == current)
				{
					first = first->link;

					if (first == NULL)
						last = NULL;

					delete current;
				}
				else
				{
					trailCurrent->link = current->link;

					if (current == last)
						last = trailCurrent;

					delete current;
				}
				count--;
			}
			else
				cout << "The item to be deleted is not in the list" << endl;
	}
}
