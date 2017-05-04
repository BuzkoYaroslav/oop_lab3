#pragma once
#include "IndexedContainer.h"
#include <string>

template <class T>
class StaticArray: public IndexedContainer<T> {
private:
	const int emptyIntValue = -1;
	
	T* elements;

	int maxNumber;
	int numberOfElements;

	bool checkIndex(int) const;
	void addElement(T const&);
public:
	int size() const;
	bool isEmpty() const;
	char* toString() const;

	T get(int) const;
	T& get(int);
	void set(int, T const&);

	StaticArray(int);
	~StaticArray();
};

template <typename T>
StaticArray<T>::StaticArray(int _maxNumber)
{
	maxNumber = _maxNumber;
	elements = new T[maxNumber];
	numberOfElements = 0;
}

template <typename T>
StaticArray<T>::~StaticArray()
{
	delete elements;
}

template <typename T>
int StaticArray<T>::size() const {
	return numberOfElements;
}

template <typename T>
bool StaticArray<T>::isEmpty() const {
	return numberOfElements == 0;
}

template <typename T>
char* StaticArray<T>::toString() const {
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

template <typename T>
bool StaticArray<T>::checkIndex(int index) const {
	return index < 0 || index >= size();
}

template <typename T>
T StaticArray<T>::get(int index) const {
	if (isEmpty()) return emptyIntValue;
	if (checkIndex(index)) return emptyIntValue;

	return elements[index];
}

template <typename T>
T& StaticArray<T>::get(int index) {
	if (isEmpty()) return emptyIntValue;
	if (checkIndex(index)) return emptyIntValue;

	return &(elements[index]);
}

template <typename T>
void StaticArray<T>::set(int index, T const& value) {
	if (index == size())
		addElement(value);
	if (checkIndex(index)) return;

	elements[index] = value;
}

template <typename T>
void StaticArray<T>::addElement(T const& value) {
	if (numberOfElements >= maxNumber) return;

	elements[numberOfElements] = value;
	numberOfElements += 1;
}