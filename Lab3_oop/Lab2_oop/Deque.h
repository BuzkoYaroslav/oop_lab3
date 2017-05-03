#pragma once
#include "Container.h"

class Deque: public virtual Container {
public:
	virtual bool pushFront(int value) = 0;
	virtual bool pushBack(int value) = 0;
	virtual int popFront() = 0;
	virtual int popBack() = 0;
	virtual int peekFront() const = 0;
	virtual int peekBack() const = 0;
	
	virtual ~Deque() = 0 {};
};