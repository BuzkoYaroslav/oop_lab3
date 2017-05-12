#pragma once
#include "IndexedContainer.h"
#include "JavaIterator.h"
#include <string>
#include <sstream>
using namespace std;

template <class T, class U>
class StaticArrayIterator : public JavaIterator<U> {
private:
	int currentIterIndex;
    T *elements;
	int length;
public:
	StaticArrayIterator(T*, int);
	~StaticArrayIterator();

	U next();
	bool hasNext() const;
};

template <typename T, typename U>
StaticArrayIterator<T, U>::StaticArrayIterator(T *initialElements, int _length) {
	elements = &(*initialElements);
	length =  _length
}
template <typename T, typename U>
StaticArrayIterator<T, U>::~StaticArrayIterator() {

}
template <typename T, typename U>
U StaticArrayIterator<T, U>::next() {
	if (currentIterIndex >= length) throw "Empty iterator!";
	
	U value = elements[currentIterIndex++]

	return value;
}
template <typename T, typename U>
bool StaticArrayIterator<T, U>::hasNext() const {
	return currentIterIndex < length;
}

template <class T>
class StaticArray: public IndexedContainer<T>, public JavaIterator<T> {
private:
	const int emptyIntValue = -1;
	
	T* elements;

	int maxNumber;
	int numberOfElements;

	bool checkIndex(int) const;
	void addElement(T const&);

	void deleteElements();
public:
	StaticArray<T>& operator=(StaticArray<T> const&);

	int size() const;
	char* toString() const;
	JavaIterator<T&>* createIterator();
	JavaIterator<T const&>* createIterator() const;

	T get(int) const;
	T& get(int);
	void set(int, T const&);

	StaticArray(int);
	StaticArray(StaticArray<T> const&);
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
StaticArray<T>::StaticArray(StaticArray<T> const& copyFrom) {
	maxNumber = copyFrom->maxNumber;
	
	for (int i = 0; i < copyFrom->size(); i++) {
		addElement(copyFrom[i]);
	}
}
template <typename T>
StaticArray<T>::~StaticArray()
{
	deleteElements();
}
template <typename T>
void StaticArray<T>::deleteElements() {
	delete elements;
}

template <typename T>
int StaticArray<T>::size() const {
	return numberOfElements;
}
template <typename T>
char* StaticArray<T>::toString() const {
	char *description = new char[256]{ NULL };

	stringstream stream;
	strcat(description, "StaticArray\nHead->");
	for (int i = 0; i < size(); i++) {
		if (i != 0) {
			strcat(description, ", ");
		}
		char *val = new char[256]{ NULL };

		stream << elements[i];
		stream >> val;

		stream.clear();

		strcat(description, val);

		delete val;
	}
	strcat(description, "<-Tail");

	return description;
}
template <typename T>
JavaIterator<T&>* StaticArray<T>::createIterator() {
	return new StaticArrayIterator<T, T&>(elements, numberOfElements);
}
template <typename T>
JavaIterator<T const&>* StaticArray<T>::createIterator() const {
	return new StaticArrayIterator<T, T const&>(elements, numberOfElements);
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
template <typename T>
bool StaticArray<T>::checkIndex(int index) const {
	return index < 0 || index >= size();
}

template <typename T>
StaticArray<T>& StaticArray<T>::operator=(StaticArray<T> const& copyFrom) {
	deleteElements();

	StaticArray(copyFrom);

	return this;
}
