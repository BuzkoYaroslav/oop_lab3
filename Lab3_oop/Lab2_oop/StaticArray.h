#pragma once
#include "IndexedContainer.h"

class StaticArray: public IndexedContainer {
private:
	const int emptyIntValue = -1;
	
	int* elements;

	int maxNumber;
	int numberOfElements;

	bool checkIndex(int) const;
	void addElement(int);
public:
	int size() const;
	bool isEmpty() const;
	char* toString() const;

	int get(int) const;
	void set(int, int);

	StaticArray(int);
	~StaticArray();
};

