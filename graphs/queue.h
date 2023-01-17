#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <cassert>

using namespace std;

template <class Type>
class queueADT
{
public:
	virtual bool isEmptyQueue() const = 0;
	virtual bool isFullQueue() const = 0;
	virtual void initializeQueue() = 0;
	virtual Type front() const = 0;
	virtual Type back() const = 0;
	virtual void addQueue(const Type& queueElement) = 0;
	virtual void deleteQueue() = 0;
};

template <class Type>
class queueType : public queueADT<Type>
{
public:
	const queueType<Type>& operator=(const queueType<Type>&);
	bool isEmptyQueue() const;
	bool isFullQueue() const;
	void initializeQueue();
	Type front() const;
	Type back() const;
	void addQueue(const Type& queueElement);
	void deleteQueue();
	queueType(int queueSize = 0);
	queueType(const queueType<Type>& otherQueue);
	~queueType();

private:
	int maxQueueSize;
	int count;
	int queueFront;
	int queueRear;
	Type* list;
};

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type>* link;
};

template <class Type>
class linkedQueueType : public queueADT<Type>
{
public:
	const linkedQueueType<Type>& operator=(const linkedQueueType<Type>&);
	bool isEmptyQueue() const;
	bool isFullQueue() const;
	void initializeQueue();
	Type front() const;
	Type back() const;
	void addQueue(const Type& queueElement);
	void deleteQueue();
	linkedQueueType();
	linkedQueueType(const linkedQueueType<Type>& otherQueue);
	~linkedQueueType();

private:
	nodeType<Type>* queueFront;
	nodeType<Type>* queueRear;
};
#endif // !QUEUE_H

template<class Type>
bool queueType<Type>::isEmptyQueue() const
{
	return (count == 0);
}
template<class Type>
bool queueType<Type>::isFullQueue() const
{
	return (count == maxQueueSize);
}
template<class Type>
void queueType<Type>::initializeQueue()
{
	queueFront = 0;
	queueRear = maxQueueSize - 1;
	count = 0;
}
template<class Type>
Type queueType<Type>::front() const
{
	assert(!isEmptyQueue());
	return list[queueFront];
}
template<class Type>
Type queueType<Type>::back() const
{
	assert(!isEmptyQueue());
	return list[queueRear];
}
template<class Type>
void queueType<Type>::addQueue(const Type& newElement)
{
	if (isFullQueue())
	{
		queueRear = (queueRear + 1) % maxQueueSize;
		count++;
		list[queueRear] = newElement;
	}
	else
		cout << "Cannot add to a full queue." << endl;
}
template<class Type>
void queueType<Type>::deleteQueue()
{
	if (!isEmptyQueue())
	{
		count--;
		queueFront = (queueFront + 1) % maxQueueSize;
	}
	else
		cout << "Cannot remove from an empty queue." << endl;
}
template<class Type>
queueType<Type>::queueType(int queueSize)
{
	if (queueSize <= 0)
	{
		cout << "Size of the array to hold queue must be positive." << endl;
		cout << "Creating  an array of size 100." << endl;
	}
	else
		maxQueueSize = queueSize;
	queueFront = 0;
	queueRear = maxQueueSize - 1;
	count = 0;
	list = new Type[maxQueueSize];
}
template<class Type>
queueType<Type>::~queueType()
{
	delete[] list;
}
template<class Type>
queueType<Type>::queueType(const queueType<Type>& otherQueue) 
{
	delete[] list;
	maxQueueSize = otherQueue.maxQueueSize;
	queueFront = otherQueue.queueFront;
	queueRear = otherQueue.queueRear;

	list = new Type[maxQueueSize];

	for (int i = 0; i < maxQueueSize; i++)
		list[i] = otherQueue.list[i];
}
template<class Type>
const queueType<Type>& queueType<Type>::operator=(const queueType<Type>& otherQueue)
{
	if (this != &otherQueue)
		queueType(otherQueue);
	return *this;
}

//queue as linkedlist
template <class Type>
bool linkedQueueType<Type>::isEmptyQueue() const
{
	return(queueFront == NULL);
} //end
template <class Type>
bool linkedQueueType<Type>::isFullQueue() const
{
	return false;
} //end isFullQueue
template <class Type>
void linkedQueueType<Type>::initializeQueue()
{
	nodeType<Type>* temp;
	while (queueFront != NULL) //while there are elements left
	//in the queue
	{
		temp = queueFront; //set temp to point to the current node
		queueFront = queueFront->link; //advance first to
		//the next node
		delete temp; //deallocate memory occupied by temp
	}
	queueRear = NULL; //set rear to NULL
} //end initializeQueue
template <class Type>
void linkedQueueType<Type>::addQueue(const Type& newElement)
{
	nodeType<Type>* newNode;
	newNode = new nodeType<Type>; //create the node
	newNode->info = newElement; //store the info
	newNode->link = NULL; //initialize the link field to NULL
	if (queueFront == NULL) //if initially the queue is empty
	{
		queueFront = newNode;
		queueRear = newNode;
	}
	else //add newNode at the end
	{
		queueRear->link = newNode;
		queueRear = queueRear->link;
	}
}//end addQueue
template <class Type>
Type linkedQueueType<Type>::front() const
{
	assert(queueFront != NULL);
	return queueFront->info;
} //end front
template <class Type>
Type linkedQueueType<Type>::back() const
{
	assert(queueRear != NULL);
	return queueRear->info;
} //end back
template <class Type>
void linkedQueueType<Type>::deleteQueue()
{
	nodeType<Type>* temp;
	if (!isEmptyQueue())
	{
		temp = queueFront; //make temp point to the first node
		queueFront = queueFront->link; //advance queueFront
		delete temp; //delete the first node
		if (queueFront == NULL) //if after deletion the
		//queue is empty
			queueRear = NULL; //set queueRear to NULL
	}
	else
		cout << "Cannot remove from an empty queue" << endl;
}//end deleteQueue
template<class Type>
linkedQueueType<Type>::linkedQueueType()
{
	queueFront = NULL; //set front to null
	queueRear = NULL; //set rear to null
} //end default constructor
