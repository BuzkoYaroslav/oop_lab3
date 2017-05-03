#pragma once
#include "Deque.h"
#include "DataNode.h"

class StaticDeque: public Deque {
private:
	const int emptyIntValue = -1;

	DataNode *head;
	DataNode *tail;

	int numberOfElements;
public:
	int size() const;
	bool isEmpty() const;
	char* toString() const;

	bool pushBack(int);
	bool pushFront(int);
	int popBack();
	int popFront();
	int peekBack() const;
	int peekFront() const;

	StaticDeque();
	~StaticDeque();
};

