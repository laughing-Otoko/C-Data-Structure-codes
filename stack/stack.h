#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <cassert>

using namespace std;

template <class Type>
class stackADT
{
public:
	virtual void initializeStack() = 0;
	virtual bool isEmptyStack() const = 0;
	virtual bool isFullStack() const = 0;
	virtual void push(const Type& newItem) = 0;
	virtual Type top() const = 0;
	virtual void pop() = 0;
};

template <class Type>
class stackType : public stackADT<Type>
{
public:
	const stackType<Type>& operator=(const stackType<Type>&);
	void initializeStack();
	bool isEmptyStack() const;
	bool isFullStack() const;
	void push(const Type& newItem);
	Type top() const;
	void pop();
	stackType(int stackSize = 100);
	stackType(const stackType<Type>& otherStack);
	~stackType();

private:
	int maxStackSize;
	int stackTop;
	Type* list;
	void copyStack(const stackType<Type>& otherStack);
};

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type>* link;
};

template <class Type>
class linkedStackType : public stackADT<Type>
{
public:
	const linkedStackType<Type>& operator=(const linkedStackType<Type>&);
	bool isEmptyStack() const;
	bool isFullStack() const;
	void initializeStack();
	void push(const Type& newItem);
	Type top() const;
	void pop();
	linkedStackType();
	linkedStackType(const linkedStackType<Type>& otherStack);
	~linkedStackType();

private:
	nodeType<Type>* stackTop;
	void copyStack(const linkedStackType<Type>& otherStack);
};
#endif // !STACK_H

template <class Type>
void stackType<Type>::initializeStack()
{
	stackTop = 0;
}
template <class Type>
bool stackType<Type>::isEmptyStack() const
{
	return (stackTop == 0);
}
template <class Type>
bool stackType<Type>::isFullStack() const
{
	return (stackTop == maxStackSize);
}
template <class Type>
void stackType<Type>::push(const Type& newItem)
{
	if (!isFullStack())
	{
		list[stackTop] = newItem;
		stackTop++;
	}
	else
		cout << "Cannot add to a full stack." << endl;
}
template <class Type>
Type stackType<Type>::top() const
{
	assert(stackTop != 0);
	return list[stackTop - 1];
}
template <class Type>
void stackType<Type>::pop()
{
	if (!isEmptyStack())
		stackTop--;
	else
		cout << "Cannot remove from an empty stack." << endl;
}
template <class Type>
void stackType<Type>::copyStack(const stackType<Type>& otherStack)
{
	delete[] list;
	maxStackSize = otherStack.maxStackSize;
	stackTop = otherStack.stackTop;
	list = new Type[maxStackSize];

	//copy otherStack into this stack
	for (int j = 0; j < stackTop; j++)
		list[j] = otherStack.list[j];
}
template <class Type>
stackType<Type>::stackType(int stackSize)
{
	if (stackSize <= 0)
	{
		cout << "Size of the array to hold the stack must be positive." << endl;
		cout << "Creating an array of size 100." << endl;

		maxStackSize = 100;
	}
	else
		maxStackSize = stackSize;

	stackTop = 0;
	list = new Type[maxStackSize];
}
template <class Type>
stackType<Type>::~stackType()
{
	delete[] list;
}
template <class Type>
stackType<Type>::stackType(const stackType<Type>& otherStack)
{
	list = NULL;
	copyStack(otherStack);
}
template <class Type>
const stackType<Type>& stackType<Type>::operator=(const stackType<Type>& otherStack)
{
	if (this != &otherStack)
		copyStack(otherStack);
	return *this;
}

//stack as linkedlist
template <class Type>
linkedStackType<Type>::linkedStackType()
{
	stackTop = NULL;
}
template <class Type>
bool linkedStackType<Type>::isEmptyStack() const
{
	return (stackTop == NULL);
}
template <class Type>
bool linkedStackType<Type>::isFullStack() const
{
	return false;
}
template <class Type>
void linkedStackType<Type>::initializeStack()
{
	nodeType<Type>* temp;
	
	while (stackTop != NULL)
	{
		temp = stackTop;
		stackTop = stackTop->link;

		delete temp;
	}
}
template <class Type>
void linkedStackType<Type>::push(const Type& newElement)
{
	nodeType<Type>* newNode;
	
	newNode = new nodeType<Type>;
	newNode->info = newElement;
	newNode->link = stackTop;
	stackTop = newNode;
}
template <class Type>
Type linkedStackType<Type>::top() const
{
	assert(stacktop != NULL);
	return stackTop->info;
}
template <class Type>
void linkedStackType<Type>::pop()
{
	nodeType<Type>* temp;
	
	if (stackTop != NULL) {
		temp = stackTop;
		stackTop = stackTop->link;

		delete temp;
	}
	else
		cout << "Cannot remove from an empty stack." << endl;
}
template <class Type>
void linkedStackType<Type>::copyStack(const linkedStackType<Type>& otherStacl)
{
	nodeType<Type>* newNode, * current, * last;

	if (stackTop != NULL)
		initializeStack();
	if(otherStack.stackTop == NULL)
		stackTop = NULL
	else
	{
		current = otherstack.stackTop;
		stackTop = new nodeType<Type>;
		stackTop->info = current->info;
		stackTop->link = NULL;
		last = stackTop;
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
linkedStackType<Type>::linkedStackType(const linkedStackType<Type>& otherStack)
{
	stackTop = NULL;
	copyStack(otherStack);
}
template <class Type>
linkedStackType<Type>::~linkedStackType()
{
	initiliazeStack();
}
template <class Type>
const linkedStackType<Type>& linkedStackType<Type>::operator=(const linkedStackType<Type>& otherStack)
{
	if (this != &otherStack)
		copyStack(otherStack);
	return *this;
}