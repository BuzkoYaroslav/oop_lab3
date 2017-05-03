#include "stdafx.h"
#include "StaticArray.h"
#include <string>

StaticArray::StaticArray(int _maxNumber)
{
	maxNumber = _maxNumber;
	elements = new int[maxNumber];
	numberOfElements = 0;
}
StaticArray::~StaticArray()
{
	delete elements;
}

int StaticArray::size() const {
	return numberOfElements;
}
bool StaticArray::isEmpty() const {
	return numberOfElements == 0;
}
char* StaticArray::toString() const {
	char *description = new char[256]{ NULL };

	strcat(description, "StaticArray\nHead->");
	for (int i = 0; i < size(); i++) {
		if (i != 0) {
			strcat(description, ", ");
		}
		char *val = new char[256]{ NULL };

		itoa(elements[i], val, 10);
		strcat(description, val);

		delete val;
	}
	strcat(description, "<-Tail");

	return description;
}

bool StaticArray::checkIndex(int index) const {
	return index < 0 || index >= size();
}

int StaticArray::get(int index) const{
	if (isEmpty()) return emptyIntValue;
	if (checkIndex(index)) return emptyIntValue;

	return elements[index];
}
void StaticArray::set(int index, int value) {
	if (index == size())
		addElement(value);
	if (checkIndex(index)) return;

	elements[index] = value;
}

void StaticArray::addElement(int value) {
	if (numberOfElements >= maxNumber) return;

	elements[numberOfElements] = value;
	numberOfElements += 1;
}