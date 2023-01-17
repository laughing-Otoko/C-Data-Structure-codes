#ifndef ARRAYLISTTYPE_H
#define ARRAYLISTTYPE_H
#include <iostream>
#include <cassert>

using namespace std;

template <class elemType>
class arrayListType
{
public:
	const arrayListType<elemType>& operator=(const arrayListType<elemType>&);
	bool isEmpty() const;
	bool isFull() const;
	int listSize() const;
	int maxListSize() const;
	void print() const;
	bool isItemAtEqual(int location, const elemType& item) const;
	void insertAt(int location, const elemType& insertItem);
	void insertEnd(const elemType& insertItem);
	void removeAt(int location);
	void retrieveAt(int location, elemType& retItem);
	void replaceAt(int location, const elemType& repItem);
	void clearList();
	int seqSearch(const elemType& item) const;
	void insert(const elemType& insertItem);
	void remove(const elemType& removeItem);
	arrayListType(int size = 100);
	arrayListType(const arrayListType<elemType>& otherList);
	~arrayListType();
	void selectionSort();
	void insertionSort();
	int partition(int first, int last);
	void swap(int first, int second);
	void recQuickSort(int first, int last);
	void quickSort();

protected:
	elemType *list; 
	int length;
	int maxSize;
	void swap(int first, int second);
	int minLocation(int first, int last);
};

template <class elemType>
class orderedArrayListType : public arrayListType<elemType>
{
public:
	orderedArrayListType(int size = 100);
	int binarySearch(const elemType& item) const;
	void insertOrd(const elemType& item);
};
#endif

template <class elemType>
bool arrayListType<elemType>::isEmpty() const
{
	return (length == 0);
}
template <class elemType>
bool arrayListType<elemType>::isFull() const
{
	return (length == maxSize);
}
template <class elemType>
int arrayListType<elemType>::listSize() const
{
	return length;
}
template <class elemType>
int arrayListType<elemType>::maxListSize() const
{
	return maxSize;
}
template <class elemType>
void arrayListType<elemType>::print() const
{
	for (int i = 0; i < length; i++)
		cout << list[i] << " ";
	cout << endl;
}
template <class elemType>
bool arrayListType<elemType>::isItemAtEqual(int location, const elemType& item) const
{
	return (list[location] == item);
}
template <class elemType>
void arrayListType<elemType>::insertAt(int location, const elemType& insertItem)
{
	if (location < 0 || location >= maxSize)
		cerr < "The position of the item to be inserted is out of range!" << endl;
	else
		if (length >= maxSize)
			cerr << "Cannot insert in a full list" << endl;
		else {
			for (int i = length; i > location; i--)
				list[i] = list[i - 1];
			list[location] = insertItem;
			length++;
		}
}
template <class elemType>
void arrayListType<elemType>::insertEnd(const elemType& insertItem)
{
	if (length >= maxSize)
		cerr << "Cannot insert in a full list!" << endl;
	else {
		list[length] = insertItem;
		length++;
	}
}
template <class elemType>
void arrayListType<elemType>::removeAt(int location)
{
	if (location < 0 || location >= length)
		cerr << "The location of the item to be removed is out of range!" << endl;
	else
	{
		for (int i = location; i < length - 1; i++)
			list[i] = list[i + 1];
		length--;
	}
}
template <class elemType>
void arrayListType<elemType>::retrieveAt(int location, elemType& retItem) const
{
	if (location < 0 || location >= length)
		cerr << "The location of the item to be retrieved is out of range!" << endl;
	else
		retItem = list[location];
}
template <class elemType>
void arrayListType<elemType>::replaceAt(int location, const elemType& repItem)
{
	if (location < 0 || location >= length)
		cerr << "The location of the item to be replaced is out of range!" << endl;
	else
		list[location] = repItem;
}
template <class elemType>
void arrayListType<elemType>::clearList()
{
	length = 0;
}
template <class elemType>
arrayListType<elemType>::arrayListType(int size)
{
	if (size < 0)
	{
		cerr << "The array size must be positive. Creating an array of size 100." << endl;
		maxSize = 100;
	}
	else
		maxSize = size;

	length = 0;
	list = new elemType[maxSize];
	assert(list != NULL)
}
template <class elemType>
arrayListType<elemType>::~arrayListType()
{
	delete[] list;
}
template <class elemType>
arrayListType<elemType>::arrayListType(const arrayListType<elemType>& otherList)
{
	maxSize = otherList.maxSize;
	length = otherList.length;
	list = new elemType[maxSize];
	assert(list != NULL);

	for (int j = 0; j < length; j++)
		list[j] = otherList.list[j];
}
template <class elemType>
const arrayListType<elemType>& arrayListType<elemType>::operator=(const arrayListType<elemType>& otherList)
{
	if (this != &otherList)
	{
		delete[] list;
		maxSize = otherList.maxSize;
		length = otherList.length;

		list = new elemType[maxSize];
		assert(list != NULL);

		for (int i = 0; i < length; i++)
			list[i] == otherList.list[i];
	}
	return *this;
}
template <class elemType>
int arrayListType<elemType>::seqSearch(const elemType& item) const
{
	int loc;
	bool found = false;

	for (loc = 0; loc < length; loc++)
		if (list[loc] == item)
		{
			found = true;
			break;
		}
	
	if (found)
		return loc;
	else
		return -1;
}
template <class elemType>
void arrayListType<elemType>::insert(const elemType& insertItem)
{
	int loc;
	if (length == 0)
		list[length++] = insertItem;
	else if (length == maxSize)
		cerr << "Cannot insert in a full list!" << endl;
	else
	{
		loc = seqSearch(insertItem);
		
		if (loc == -1)
			list[length++] = insertItem;
		else
			cerr << "The item to be inserted is already in the list. No duplicates are allowed!" << endl;
	}
}
template <class elemType>
void arrayListType<elemType>::remove(const elemType& removeItem)
{
	int loc;

	if (length == 0)
		cerr << "Cannot delete from an empty list!" << endl;
	else
	{
		loc = seqSearch(removeItem);
		if (loc != -1)
			removeAt(loc);
		else
			cout << "Item to be deleted is not in the list!" << endl;
	}
}
template<class elemType>
int arrayListType<elemType>::minLocation(int first, int second)
{
	int minIndex;
	
	minIndex = first;

	for (int loc = first + 1; loc <= last; loc++)
		if (list[loc] < list[minIndex])
			minIndex = loc;
	return minIndex;
}
template <class elemType>
void arrayListType<elemType>::swap(int first, int second)
{
	elemType temp;

	temp = list[first];
	list[first] = list[second];
	list[second] = temp;
}
template <class elemType>
void arrayListType<elemType>::selectionSort()
{
	int minIndex;
	
	for (int loc = 0; loc < length - 1; loc++)
	{
		minIndex = minLocation(loc, length - 1);
		swap(loc, minIndex);
	}
}
template <class elemType>
void arrayListType<elemType>::insertionSort()
{
	int firstOutOfOrder, location;
	elemType temp;

	for (firstOutOfOrder = 1; firstOutOfOrder < length; firstOutOfOrder++)
		if (list[firstOutOfOrder] < list[firstOutOfOrder - 1])
		{
			temp = list[firstOutOfOrder];
			location = firstOutOfOrder;

			do
			{
				list[location] = list[location - 1];
				location--;
			} while (location > 0 && list[location - 1] > temp);

			list[location] = temp;
		}
}

template <class elemType>
void arrayListType<elemType>::swap(int first, int second)
{
	elemType temp;
	temp = list[first];
	list[first] = list[second];
	list[second] = temp;
}
template <class elemType>
void arrayListType<elemType>::recQuickSort(int first, int last)
{
	int pivotLocation;
	if (first < last)
	{
		pivotLocation = partition(first, last);
		recQuickSort(first, pivotLocation - 1);
		recQuickSort(pivotLocation + 1, last);
	}
}
template <class elemType>
void arrayListType<elemType>::quickSort()
{
	recQuickSort(0, length - 1);
}
//orderedArrayListType
template <class elemType>
int orderedArryListType<elemType>::binarySearch(const elemType& item) const
{
	int first = 0;
	int last = length - 1;
	int mid;
	bool found = false;

	while (first <= last && !found) {
		mid = (first + last) / 2;
		if (list[mid] == item)
			found = true;
		else if (list[mid] > item)
			last = mid - 1;
		else
			first = mid + 1;
	}
	if (found)
		return mid;
	else
		return -1;
}
template <class elemType>
void orderedArrayListType<elemType>::insertOrd(const elemType& item)
{
	int first = 0;
	int last = length - 1;
	int mid;
	bool found = false;

	if (length == 0)
	{
		list[0] = item;
		length++;
	}
	else if (length == maxSize)
		cerr << "Cannot insert into full list." << endl;
	else
	{
		while (first <= last && !found)
		{
			mid = (first + last) / 2;
			
			if (list[mid] == item)
				found = true;
			else if (list[mid] > item)
				last = mid - 1;
			else
				first = mid + 1;
		}
		if (found)
			cerr << "The insert item is already in the list. "
				 << "Duplicates are not allowed." << endl;
		else
		{
			if (list[mid] < item)
				mid++;
			insertAt(mid, item);
		}
	}


}

