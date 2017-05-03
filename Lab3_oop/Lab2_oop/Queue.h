#pragma once
#include "PushPopContainer.h"
#include "DataNode.h"

class Queue: public PushPopContainer {
private:
	DataNode *head;
	DataNode *tail;

	int numberOfElements;
public:
	int size() const;
	bool isEmpty() const;
	char* toString() const;

	int pop();
	int peek() const;
	bool push(int);

	Queue();
	~Queue();
};

