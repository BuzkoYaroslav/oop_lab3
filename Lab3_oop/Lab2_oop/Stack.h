#pragma once
#include "PushPopContainer.h"
#include "DataNode.h"

class Stack: public PushPopContainer {
private:
	DataNode *head;
	int numberOfElements;
public:
	int size() const;
	bool isEmpty() const;
	char * toString() const;

	int peek() const;
	int pop();
	bool push(int);

	Stack();
	~Stack();
};

