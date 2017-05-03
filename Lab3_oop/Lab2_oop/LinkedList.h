#pragma once
#include "InsertableContainer.h"
#include "PushPopContainer.h"
#include "DataNode.h"

class LinkedList: public InsertableContainer, public PushPopContainer
{
private:
	const int emptyIntValue = -1;

	DataNode *head;
	DataNode *tail;

	int numberOfElements;

	bool checkIndex(int) const;

	DataNode* elementAtIndex(int) const;
public:
	// Container
	int size() const;
	bool isEmpty() const;
	char* toString() const;

	// PushPopContainer
	bool push(int);
	int peek() const;
	int pop();

	// IndexedContainer
	int get(int) const;
	void set(int, int);

	// Deque
	bool pushFront(int);
	bool pushBack(int);
	int popFront();
	int popBack();
	int peekFront() const;
	int peekBack() const;

	// InsertableContainer
	bool insertAt(int, int);
	int removeAt(int);

	LinkedList();
	~LinkedList();
};

