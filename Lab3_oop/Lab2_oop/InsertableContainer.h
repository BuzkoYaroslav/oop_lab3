#pragma once
#include "IndexedContainer.h"
#include "Deque.h"

class InsertableContainer: public IndexedContainer, public Deque {
public:
	virtual bool insertAt(int index, int value) = 0;
	virtual int removeAt(int index) = 0;

	virtual ~InsertableContainer() = 0 {};
};